# Project 3: Where am I?

## Checklist

* [ ] Basic Requirements
    - [ ] ROS Package containing AMCL, teleop, robot, world and map files
    - [ ] Screenshot(s) of localized robot in RViz

* [ ] Simulation Setup
    - [ ] Student's simulation world and robot could properly load in Gazebo.
    - [ ] Student's simulation setup should have the appropriate number of landmarks or geometric features to perform localization.

* [ ] Localization Setup
    - [ ] Student's launch file contains all required nodes: 
        * [ ] Map Server node `map_server` 
        * [ ] AMCL node `amcl` 
        * [ ] Move Base node `move_base` 
        * [ ] The student's program should be able to launch without errors
    - [ ] Student filled required parameters for AMCL and move_base in the launch file and the config file

* [ ] Localization Performance
    - [ ] Student's robot could quickly localize itself after being tele-operated in the student's world, or given nav_goal target.

