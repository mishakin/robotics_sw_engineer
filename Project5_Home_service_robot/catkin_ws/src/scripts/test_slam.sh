#!/bin/sh
xterm  -e  " roslaunch my_robot my_robot_world.launch " &
sleep 5
xterm  -e  " roslaunch my_robot gmapping_demo.launch " &
sleep 5
xterm  -e  " roslaunch my_robot view_navigation.launch " &
sleep 5
xterm  -e  " rosrun teleop_twist_keyboard teleop_twist_keyboard.py " &
