/**
   @author Kenta Suzuki
*/

#include <cnoid/Format>
#include <cnoid/Plugin>
#include <cnoid/WRSUtilBar>

using namespace cnoid;

class WRS2025Plugin : public Plugin
{
public:
    WRS2025Plugin()
        : Plugin("WRS2025")
    {
        require("Body");
        require("WRSUtil");
    }

    virtual bool initialize() override
    {
        WRSUtilBar::instance()->addFormat({ "WRS2025", 25.0 });
        return true;
    }

    virtual const char* description() const override
    {
        static std::string text =
            formatC("WRS2025 Plugin Version {}\n", CNOID_FULL_VERSION_STRING) +
            "\n" +
            "Copyright (c) 2025 WRS Simulation Disaster Challenge Competition Committee.\n"
            "\n" +
            MITLicenseText();
        return text.c_str();
    }
};

CNOID_IMPLEMENT_PLUGIN_ENTRY(WRS2025Plugin)