# Gazebo Installation Tutorials

#**RBE 500 Fall** #_Made by Prof. Berk Calli and Yash Patil_

In this tutorial we will install Gazebo 11 and all its supporting files that will aid us in robot simulation.

## Gazebo

Use the following commands to install Gazebo and its supplementry files

```
sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'

wget https://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
```

Once this is done, update using and make sure it runs without any errors

```
sudo apt-get update
```

now install Gazebo using

```
sudo apt-get install gazebo libgazebo-dev
```

You can check your installation by running this in a new terminal

```
gazebo
```

## Gazebo ROS 2 packages

To use Gazebo with ros2, there are certain packages that need to be installed

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

## Spawn rrbot in Gazebo

These are optional steps just to make sure everything is alright.

Please find the zipped package that has one of many ways to spawn an URDF in Gazebo using ROS2.

Extract the package to your workspace/src.

Before doing `colcon build` we have to install some dependencies for the package to function correctly.
Run the following commands in terminal

```
sudo apt install python3-pip
sudo pip3 install transforms3d
```

Once you have successfully installed all the required packages, find the supporting zip file that contains rrbot simulation files.

## RRBOT

That zip file contains 2 packages
**rrbot_description**
**rrbot_gazebo**

### rrbot_description

This package contains the description files for the rrbot such as its urdf, gazebo plugins, ros2 control definitions etc.
Xacro has been used instead of URDF to keep the description more modular, you will find that the main file *rrbot.urdf.xacro* includes a bunch of different files, so you don't have to deal with a very large file.
The important files for us are *rrbot.gazebo.xacro* and *rrbot.ros2_control.xacro*, these contains the configuration for ROS2 Control.
Visit this link for understanding how to configure ros2 control for your robot: https://github.com/ros-controls/gazebo_ros2_control

### rrbot_gazebo

This package launches the actual simulation environment.
The *gazebo_controllers.yaml* file in *config* helps us define what kind of controller we want to use, here we are using a **forward_command_controller** that just takes the command and applies it as it is, we have selected position as the command interface, i.e. we will control the position of the joints, reset all will be calculated by the controller. We can also use velocity or effort (torque) as the command interface.
The state interfaces is what kind of feedback we will receive from **JointStateBroadcastser**, here we are taking position, velocity and effort feedbacks from the robot.
**JointStateBroadcaster** is a different type of controller, it basically reads the current joint states from simulation environment and publishes it on the topic */joint_states*.

The launch folder contains a launch file **rrbot_world.launch.py** which will be used to launch every thing, gazebo simulation environment, controller manager for ros2 control, robot state publisher.

## For Simulation

Extract the zip file to your ros2 workspace and cd in your workspace

```
colcon build --symlink-install
. install/setup.bash
```

As we are using some gazebo plugins for camera, we need to source the gazebo setup bash file too

```
. /usr/share/gazebo/setup.bash
```

you can also put this in your .bashrc by doing

```
echo ". /usr/share/gazebo/setup.bash" >> ~/.bashrc
```

Now open a new terminal and run

```
ros2 launch rrbot_gazebo rrbot_world.launch.py
```

This should result in a new Gazebo window popping up with rrbot spawned,
Now if you do ros2 topic list, you will be able to see a bunch of different topics
*/joint_states* : This topic will have the robot's current state, i.e. position, velocity and efforts of each joint
*/forward_position_controller/commands* : This is the control topic, this will be used to control the robot joints
*/camera1/image_raw* : On this topic the robot will publish the camera feed, to visualize what the camera is seeing we can use rviz2.

open a new terminal and run

```
ros2 run rviz2 rviz2
```

A new window with Rviz should open up, first set the 'Fixes Frame' to *world*, and then click on 'Add', Select 'By Topic', and then select 'image'. You will be able to see a small dialog box on left hand side with the current feed of camera.

Now open up a new terminal and run

```
ros2 run rrbot_gazebo publisher
```

*Note: This can also result in your system getting hanged for a few minutes, this is just a first time thing and please don't kill the node if this happens, average hang-time is around 2-3 mins, if it goes above 10 mins kill the launch file.*

### You can refer to this package and understand how the robots can be spawned in Gazebo.
