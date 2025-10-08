## Introducing your robots to the environment

This page explains the procedure for placing your robot models in the practice environment when loading them. The main steps are as follows:
1. Copy the robot model file
2. Create a project
3. Create a YAML file
4. Start Choreonoid
5. About simulation performance

### 1. Copy the robot model file
First, create a directory with any name (e.g., ``model_<team name>``) under ``choreonoid/ext/WRS2025/model``, and copy all your custom robot model files and directories into that directory.

Next, rebuild Choreonoid. If you are using Choreonoid in a ROS2 environment, the files you added may not be recognized during the rebuild. In that case, add the option ``–cmake-clean-cache`` when rebuilding.

Once the rebuild is complete, if you are using Choreonoid in a ROS2 environment, check the following directory: ``ros2_ws/install/choreonoid/share/choreonoid-x.x/WRS2025/model`` . If you are using Choreonoid standalone, check the following directory: ``choreonoid/build/share/choreonoid-x.x/WRS2025/model``. Replace ``choreonoid-x.x`` with the version of Choreonoid you are using. 
If the directory created in the previous step (e.g., ``model_<team name>``) exists in the directory, this procedure is complete.

### 2. Create a project
Here, we will create a project to save the robot model. Launch Choreonoid. If you are using Choreonoid in a ROS2 environment, load the custom robot model from the following directory: ``ros2_ws/install/choreonoid/share/choreonoid-x.x/WRS2025/model``. If you are using Choreonoid standalone, load the custom robot model from the following directory: ``choreonoid/build/share/choreonoid-x.x/WRS2025/model`` .
Replace ``choreonoid-x.x`` with the version of Choreonoid you are using.

After importing your custom robot model, configure all necessary simple controllers and other components.
If you are using Choreonoid in a ROS2 environment and need to publish information from devices such as cameras or range sensors, add a BodyROS2 item as a child item of the robot model.

Once the settings are complete, if you are using Choreonoid in a ROS2 environment, run the following command: If you are using Choreonoid standalone, create a directory with any name (e.g., ``project_<team name>``) under ``choreonoid/ext/WRS2025/project``, and save the project (``.cnoid``) file in this directory.
Save the project with the name of your custom robot model.
**The name of the project saved here will be used in the “Creating the YAML file” section below.**
Next, rebuild Choreonoid. If you are using Choreonoid in a ROS2 environment, the files you added may not be recognized during the rebuild. In that case, add the option ``–cmake-clean-cache`` .

After rebuilding, if you are using Choreonoid in the ROS2 environment, check the directory under ``ros2_ws/install/choreonoid/share/choreonoid-x.x/WRS2025/project`` . If you are using Choreonoid standalone, check the directory under ``choreonoid/build/share/choreonoid-x.x/WRS2025/project`` . Replace ``choreonoid-x.x`` with the version of Choreonoid you are using. 

If the directory created in the previous step (e.g., ``project_<team name>``) exists in the directory, this procedure is complete.

### 3. Create a YAML file
Create a YAML file to be used for loading the practice environment. Here, we will use ``registration_m3.yaml`` stored in ``WRS2025/registration`` as a template. Copy ``registration_m3.yaml`` to any directory and rename it to any name (e.g., ``registration_m3_<team name>.yaml``).
Open the YAML file in any text editor and replace the second line with the following:
```
robot_list: &RobotList  [ <Name of the created directory>/<Name of the project where the custom robot model is saved> ]
```
For example, if the team name is ``team1``, the directory name is ``project_team1``, and the name of the project saved in the previous step is ``my_robot.cnoid``,

```
robot_list: &RobotList [ project_team1/my_robot ]
```
Rewrite it as shown above.
In addition to your own robot models, you can use the following standard robot models.

| Project name | Explanation |
| ---- | ---- |
| ``AizuSpiderDA-ROS2`` | AizuSpiderDS for AGX simulators. AizuSpiderDS subscribes to the /joy topic of ROS2's sensor_msgs::msg::Joy . |
| ``AizuSpiderDS-ROS2`` | AizuSpiderDS for AIST Simulator. AizuSpiderDS subscribes to the /joy topic of ROS2's sensor_msgs::msg::Joy . |
| ``HobbyDrone-ROS2`` | HobbyDrone. HobbyDrone subscribes to the ROS2 sensor_msgs::msg::Joy/joy2 topic . |

For example, if you want to use AizuSpider (``AizuSpiderDA-ROS2``) for the AGX simulator in the ROS environment together with your own robot model (``my_robot``), please modify the first line of the YAML file as follows.

```
robot_list: &RobotList [ project_team1/my_robot, AizuSpiderDA-ROS2 ]
```
With this configuration, when the practice environment is loaded, my_robot will be positioned on the left side and AizuSpiderDA on the right side. To swap the positions, reorder the list and modify it as follows:
```
robot_list: &RobotList [ AizuSpiderDA-ROS2, project_team1/my_robot ]
```
After saving the YAML file, this procedure is complete.

### 4. Start Choreonoid
Please start Choreonoid with the following command. If you are using Choreonoid in a ROS2 environment,

```
$ ros2 run choreonoid_ros choreonoid <path/to/yaml> --wrs-util <mission_name>
```

When using Choreonoid alone (e.g., within ```choreonoid/build```),
```
$ ./bin/choreonoid <path/to/yaml> --wrs-util <mission_name>
```
Enter the following. Be careful about the order of the arguments. For ```<path/to/yaml>```, enter the path to the YAML file created in the previous step as an argument. The arguments that can be specified with ```<mission_name>``` are as follows.

| Arguments | Explanation |
| ---- | ---- |
| ``M3`` | Loading practice environment |


When you start Choreonoid, if the robot model is misaligned, adjust the initial position coordinates [x, y, z] using start_position. Here, coordinates are specified in meters.
This completes the loading of the practice environment.

### 5. About simulation performance
In WRS2025, there are no custom robot regulations except for simulation performance.
It is desirable that the value, the ratio of real time to simulation time, output by the Choreonoid when the simulation is complete, be as close to 1.0 as possible.
