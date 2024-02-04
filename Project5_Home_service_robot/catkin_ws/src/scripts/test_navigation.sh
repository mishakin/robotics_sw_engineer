#!/bin/sh
xterm  -e  " roslaunch my_robot my_robot_world.launch " &
sleep 3
xterm  -e  " roslaunch my_robot amcl_demo.launch " &
sleep 3
xterm  -e  " roslaunch my_robot view_navigation.launch " &

