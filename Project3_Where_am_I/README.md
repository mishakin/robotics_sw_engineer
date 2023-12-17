# Project 3: Where am I?

## GIF of localization performance

### Before AMCL parameters optimization

![Before AMCL parameters optimization](illustrations/where_am_I_before_parameter_tuning.gif) 

### After AMCL parameters optimization

![Before AMCL parameters optimization](illustrations/where_am_I_after_parameter_tuning.gif) 

## How to run

1. Clone the repo `git clone https://github.com/mishakin/robotics_sw_engineer.git`
2. `cd robotics_sw_engineer/Project3_Where_am_I/catkin_ws/src`
3. `catkin_init_workspace`
4. `cd ..`
5. `catkin_make`
6. `source devel/setup.bash`
7. `roslaunch my_robot main.launch`
8. Navigate the robot using keyboard (the terminal in which the previous command was fired, should be in focus)

## Checklist

* [x] Basic Requirements
    - [x] ROS Package containing AMCL, teleop, robot, world and map files
    - [x] Screenshot(s) of localized robot in RViz

* [x] Simulation Setup
    - [x] Student's simulation world and robot could properly load in Gazebo.
    - [x] Student's simulation setup should have the appropriate number of landmarks or geometric features to perform localization.

* [x] Localization Setup
    - [x] Student's launch file contains all required nodes: 
        * [x] Map Server node `map_server` 
        * [x] AMCL node `amcl` 
        * [x] ~~Move Base node `move_base`~~ Tele operator is used instead  
        * [x] The student's program should be able to launch without errors
    - [x] Student filled required parameters for AMCL ~~and move_base~~ (tele operator is used instead) in the launch file and the config file

* [x] Localization Performance
    - [x] Student's robot could quickly localize itself after being tele-operated in the student's world, or given nav_goal target.

