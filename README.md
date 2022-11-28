# Table of Contents
- [Table of Contents](#table-of-contents)
- [Introduction](#introduction)
- [How to setup the project](#how-to-setup-the-project)
  - [Install ROS2 Humble Hawksbill](#install-ros2-humble-hawksbill)
  - [Environment Setup](#environment-setup)
  - [Gazebo Installation Tutorials](#gazebo-installation-tutorials)
  - [Simulation](#simulation)
- [How to use the project](#how-to-use-the-project)
  - [Assignment 1](#assignment-1)
    - [**Forward Kinematics Node**](#forward-kinematics-node)
    - [**Inverse Kinematics Node**](#inverse-kinematics-node)
  - [Assignment 2](#assignment-2)
    - [**Joint Efforts Control Node**](#joint-efforts-control-node)
  - [Assignment 3](#assignment-3)
- [Tools Used](#tools-used)
- [Designer Details](#designer-details)

# Introduction
The aim of the assignment is meant to get a better understanding of basic concepts of Robotics using tools like [ROS2 Humble Hawksbill](https://docs.ros.org/en/humble/index.html), [Gazebo Sim](https://gazebosim.org/home), [RVIZ](https://github.com/ros2/rviz) and [MathWorks&#174; MATLAB](https://www.mathworks.com/products/matlab.html)

The final project is divided into three seperate assignments:

1. Assignment 1: Build Model URDF, Forward Kinematics Node and Inverse Kinematics Node.
   1. Setup the dynamically accurate model of robot in Gazebo by editing the model URDF.
   2. Calculate the DH Parameters of the Robot to build a node that:
      1. Subscribes to the joint states of the robot and calculates the Pose of the robot by using Forward Kinematics.
      2. Publishes the Pose of the Robot to a new topic using a publisher.
   3. Create an Inverse Kinematics Calculation Node that:
      1. Uses a custom service to take input of the (x,y,z) coordinates of the robot end-effector.
      2. Calculate the Joint States from the end-effector position and return it as a response to the service.
2. Assignment 2: Build a node to control Joint States.
   1. Create a node that takes:
      1. Reference Values for Joint States as input through a service.
      2. Build a Proportional-Derivative Controller that takes the current Joint States and Reference joint state to publish the control torque values to the **/forward_effort_controller/commands** topic.
      3. Ensure that the model reaches the reference joint states in Gazebo.
3. Assignment 3:

 *Note: This project is designed on Ubuntu 22.04 LTS and not tested on any other platforms*

*Super Note: Remember, If anything doesnt work as it is supposed to, just use the rules of IT. Close it and restart it again :)*

# How to setup the project

## Install ROS2 Humble Hawksbill

**Set locale**

Make sure you have a locale which supports `UTF-8`. If you are in a minimal environment (such as a docker container), the locale may be something minimal like `POSIX`. We test with the following settings. However, it should be fine if you’re using a different UTF-8 supported locale.
```
locale  # check for UTF-8

sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

locale  # verify settings
```

**Setup Sources**

You will need to add the ROS 2 apt repository to your system.

First ensure that the [Ubuntu Universe repository](https://help.ubuntu.com/community/Repositories/Ubuntu) is enabled.
```
sudo apt install software-properties-common
sudo add-apt-repository universe
```
Now add the ROS 2 GPG key with apt.
```
sudo apt update && sudo apt install curl
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
```
Then add the repository to your sources list.
```
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```
**Install ROS 2 Packages**

Update your apt repository caches after setting up the repositories.
```
sudo apt update
```
ROS 2 packages are built on frequently updated Ubuntu systems. It is always recommended that you ensure your system is up to date before installing new packages.
```
sudo apt upgrade
```
Desktop Install (Recommended): ROS, RViz, demos, tutorials.
```
sudo apt install ros-humble-desktop -y
```

## Environment Setup
**Sourcing the setup script**

Set up your environment by sourcing the following file.
```
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
```
**Extra steps just to ensure colcon is properly installed**

The [ROS project](https://www.ros.org/) hosts copies of the Debian packages in their apt repositories.
```
sudo sh -c 'echo "deb [arch=amd64,arm64] http://repo.ros2.org/ubuntu/main `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list'
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
```
After that you can install the Debian package which depends on `colcon-core` as well as commonly used extension packages (see [setup.cfg](https://github.com/colcon/colcon-common-extensions/blob/master/setup.cfg)).
```
sudo apt update
sudo apt install python3-colcon-common-extensions
```
## Gazebo Installation Tutorials
In this tutorial we will install Gazebo 11 and all its supporting files that will aid us in robot simulation.

**Gazebo**

Use the following commands to install Gazebo and its supplementry files

```
sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
wget https://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
```
Once this is done, update using and make sure it runs without any errors
```
sudo apt-get update
```
Now install Gazebo using
```
sudo apt-get install gazebo libgazebo-dev
```
You can check your installation by running this in a new terminal
```
gazebo
```
**Gazebo ROS 2 packages**

To use Gazebo with ROS2, there are certain packages that need to be installed

```
sudo apt install ros-humble-gazebo-ros-pkgs
```
Now we will install simulated robot controllers
```
sudo apt-get install ros-humble-ros2-control ros-humble-ros2-controllers
sudo apt-get install ros-humble-gazebo-ros2-control ros-humble-xacro
sudo apt-get install ros-humble-joint-state-publisher ros-humble-joint-state-publisher-gui
```
Now your system is ready to simulate any robot.

**Spawn rrbot in Gazebo**

Before doing `colcon build` we have to install some dependencies for the package to function correctly.
Run the following commands in terminal

```
sudo apt install python3-pip
sudo pip3 install transforms3d
```

These are optional steps just to make sure everything is alright:
- Please find the zipped package that has one of many ways to spawn an URDF in Gazebo using ROS2. The true and unedited files can be found in the directory: `/Resources/Group Project 1/rrbot_simulation_files.zip`
- Extract the package to your `/src`.

Once you have successfully installed all the required packages, find the supporting zip file that contains rrbot simulation files.

**RRBOT:**

That zip file contains 2 packages:
- **rrbot_description**:
This package contains the description files for the rrbot such as its urdf, gazebo plugins, ros2 control definitions etc.
Xacro has been used instead of URDF to keep the description more modular, you will find that the main file *rrbot.urdf.xacro* includes a bunch of different files, so you don't have to deal with a very large file.
The important files for us are *rrbot.gazebo.xacro* and *rrbot.ros2_control.xacro*, these contains the configuration for ROS2 Control.
Visit this link for understanding how to configure ros2 control for your robot: https://github.com/ros-controls/gazebo_ros2_control

- **rrbot_gazebo:**
This package launches the actual simulation environment.
The *gazebo_controllers.yaml* file in *config* helps us define what kind of controller we want to use, here we are using a **forward_command_controller** that just takes the command and applies it as it is, we have selected position as the command interface, i.e. we will control the position of the joints, reset all will be calculated by the controller. We can also use velocity or effort (torque) as the command interface.
The state interfaces is what kind of feedback we will receive from **JointStateBroadcastser**, here we are taking position, velocity and effort feedbacks from the robot.
**JointStateBroadcaster** is a different type of controller, it basically reads the current joint states from simulation environment and publishes it on the topic */joint_states*.

The launch folder contains a launch file **rrbot_world.launch.py** which will be used to launch every thing, gazebo simulation environment, controller manager for ros2 control, robot state publisher.

## Simulation

In the main folder run the following commands:
```
colcon build --symlink-install
. install/setup.bash
```
As we are using some gazebo plugins for camera, we need to source the gazebo setup bash file too
```
echo ". /usr/share/gazebo/setup.bash" >> ~/.bashrc
```
Now open a new terminal to launch rrbot in gazebo and run
```
ros2 launch rrbot_gazebo rrbot_world.launch.py
```

This should result in a new Gazebo window popping up with rrbot spawned,
Now if you do ros2 topic list, you will be able to see a bunch of different topics
*/joint_states* : This topic will have the robot's current state, i.e. position, velocity and efforts of each joint
*/forward_position_controller/commands* : This is the control topic, this will be used to control the robot joints
*/camera1/image_raw* : On this topic the robot will publish the camera feed, to visualize what the camera is seeing we can use rviz2.

*Note: This can also result in your system getting hanged for a few minutes, this is just a first time thing and please don't kill the node if this happens, average hang-time is around 2-3 mins, if it goes above 10 mins kill the launch file.*

<br>

# How to use the project
## Assignment 1
1. Compile the project by using the command:
   ```
   colcon build
   ```
### **Forward Kinematics Node**

2. Launch the RVIZ model in a new terminal using:
   ```
   ros2 launch rrbot_description view_robot.launch.py 
   ```
   This will launch a Rviz windows which shows the robot model along with a a small window titled **Joint State Publisher** with three sliders to control three joints.
   
   1. Rviz Model Window:
      ![RViz Model Window](/Submissions/Group%20Project%201/RVIZ%20Window.png)
   2. Joint Publisher Model:

      ![Joint State Publisher Window](/Submissions/Group%20Project%201/Joint%20State%20Publisher%20Window.png)
3. In a new Terminal, Launch the Forward Kinematics node using:
   ```
   ros2 run rrbot_gazebo fkin_publisher
   ```
   The Node will take the Joint States from the topic `/joint_states` in the format `sensor_msgs::msg::JointState`

   The Calculated Pose is published on the topic `/forward_position_controller/commands` in format `std_msgs::msg::Float64MultiArray`
4. In a new Terminal, Echo the Forward Kinematics Topic using
   ```
   ros2 topic echo /forward_position_controller/commands
   ```
   The output data will be displayed as follows:

      ![FKIN Topic Echo](/Submissions/Group%20Project%201/FKIN%20Topic%20Echo.png)
    
    The x coordinates is displayed at line 4.

    The y coordinates is displayed at line 8.
    
    The z coordinates is displayed at line 12.
5. Move around the sliders in the *Joint State Publisher* Window to see the End Effector Position change.

### **Inverse Kinematics Node**

The Inverse Kinematics Node works on a server service node setup. The user can type the end-effector pose after launching the server node and request node to calculate the Joint States using a Service Call.

6. In a new terminal (*You can close all other terminals if you wish to*), Launch the Inverse Kinematics Server Node using:
   ```
   ros2 run rrbot_gazebo ikin_publisher
   ```
7. In a new terminal launch the service using
   ```
   ros2 service call /inverse_kinematics custom_interfaces/srv/FindJointStates "{x: 1, y: 0, z: 2}"
   ```
   Change the end effector position by changing the values for (x,y,z).

   The service Call will return the output in following format:
   
   ![IKIN Service Call](/Submissions/Group%20Project%201/Ikin%20Service%20Call.png)
    
    The service results two sets of possible response:
    - (q11, q21, q31)
    - (q12, q22, q32)

## Assignment 2
1. Compile the project by using the command:
   ```
   colcon build
   ```
2. Launch RRBOT in Gazebo using:
   ```
   ros2 launch rrbot_gazebo rrbot_world.launch.py 
   ```
   This will launch the Gazebo Window with the RRBOT spawned.
   
   ![RRBOT Gazebo Spawn](/Submissions/Group%20Project%202/Gazebo%20Model.png)
### **Joint Efforts Control Node**
3. Launch the Joint Control Node using:
   ```
   ros2 run rrbot_gazebo joint_control
   ```
   The control strategy used for the Joint Control Strategy is PD Control. The system is broken down into individual joints where each joint has it's own control system. This strategy divides the whole system into 3 individual SISO System allowing us to tune Kp and Kd parameters individually.
   $$u = -K_{p}*e_{x} - K_{d}*e_{v}$$
   where:
   - $e_{x}$ is position error: $e_{x} = x_{reference} - x_{current}$
   - $e_{v}$ is velocity error: $e_{v} = v_{reference} - v_{current}$
4. Call the Joint Control service using:
   ```
   ros2 service call /joint_state_controller custom_interfaces/srv/SetJointStates '{rq1: 1, rq2: 2, rq3: 2}'
   ```
   Change the Joint States by trying different values for (rq1,rq2,rq3)

   ![Example Video](https://github.com/parth-20-07/RBE-500-Final-Project/blob/41c92a89b4cd3c61b09122e709d2747ececefb5c/Submissions/Group%20Project%202/Robot%20Joint%20Control.mp4)

## Assignment 3


# Tools Used
<img width="30px" align="left" alt="C" src="Resources/Logos/C Logo.jpeg">
<img width="25px" align="left" alt="CPP" src="Resources/Logos/CPP Logo.jpeg">
<img width="80px" align="left" alt="Git" src="Resources/Logos/Git Logo.jpeg">
<img width="35px" align="left" alt="GitHub" src="Resources/Logos/GitHub Logo.jpeg">
<img width="35px" align="left" alt="VS Code" src="Resources/Logos/VS Code.jpeg">

<br><br>

# Designer Details
- Designed for: 
  - Worcester Polytechnic Institute
  - RBE 500: Foundation of Robotics - Final Project
- Designed by:
  - [Parth Patel](mailto:parth.pmech@gmail.com)
  - [Kamron Schloer](mailto:)