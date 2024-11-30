/**
    Storage Controller
    @author Kenta Suzuki
*/

#include <cnoid/MathUtil>
#include <cnoid/SimpleController>
#include <vector>

using namespace cnoid;

class StorageController : public SimpleController
{
    SimpleControllerIO* io;
    Link* buttonJoint[2];
    Link* shutter;
    double qref[2];
    double qprev[2];
    double dq_target;
    double dt;

    struct ActionInfo {
        int actionId;
        int buttonId;
        bool prevButtonState;
        bool stateChanged;
        ActionInfo(int actionId, int buttonId)
            : actionId(actionId),
              buttonId(buttonId),
              prevButtonState(false),
              stateChanged(false)
        { }
    };
    std::vector<ActionInfo> actions;

public:

    virtual bool initialize(SimpleControllerIO* io) override
    {
        this->io = io;
        std::ostream& os = io->os();
        Body* body = io->body();

        buttonJoint[0] = body->link("BUTTON_G");
        buttonJoint[1] = body->link("BUTTON_R");
        for(int i = 0; i < 2; ++i) {
            Link* joint = buttonJoint[i];
            if(!joint) {
                os << "Button joint " << i << " is not found." << std::endl;
                return false;
            }
            qref[i] = qprev[i] = joint->q();
            joint->setActuationMode(Link::JointEffort);
            io->enableIO(joint);
        }

        shutter = body->link("SHUTTER");
        if(!shutter) {
                os << "The  shutter is not found." << std::endl;
                return false;
        }
        dq_target = 0.0;
        shutter->setActuationMode(Link::JointVelocity);
        io->enableIO(shutter);

        dt = io->timeStep();

        actions = {
            { 0, 0 },
            { 1, 1 }
        };

        return true;
    }

    virtual bool control() override
    {
        static const double P = 10.0;
        static const double D = 5.0;

        bool getButtonState[2];
        for(int i = 0; i < 2; ++i) {
            Link* joint = buttonJoint[i];
            double q = joint->q();
            double q_upper = joint->q_upper();
            double q_lower = joint->q_lower();
            double dq = (q - qprev[i]) / dt;
            double dqref = 0.0;
            qref[i] = 0.005;
            joint->u() = P * (qref[i] - q) + D * (dqref - dq);
            qprev[i] = q;

            getButtonState[i] = q < 0.001 ? true : false;
        }

        for(auto& info : actions) {
            bool stateChanged = false;
            bool buttonState = getButtonState[info.buttonId];
            if(buttonState && !info.prevButtonState) {
                stateChanged = true;
            }
            info.prevButtonState = buttonState;
            if(stateChanged) {
                dq_target = info.actionId == 0 ? 0.2 : -0.2;
                std::string button_name = info.actionId == 0 ? "green" : "red";
                io->os() << "The " + button_name + " button has been pushed." << std::endl;
            }
        }

        double q2 = shutter->q();
        double q2_upper = shutter->q_upper();
        double q2_lower = shutter->q_lower();

        if((q2 > q2_upper && dq_target > 0.0) || (q2 < q2_lower && dq_target < 0.0)) {
            dq_target = 0.0;
        }

        shutter->dq_target() = dq_target;

        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(StorageController)