#!/bin/sh
xterm -e " cd catkin_ws/ "
xterm -e " catkin_make "
xterm -e " source devel/setup.bash "
xterm -e " roslaunch my_robot warehouse_world.launch " &
sleep 5
xterm -e " source devel/setup.bash "
xterm -e " roslaunch my_robot warehouse_amcl.launch " &
sleep 5
xterm -e " source devel/setup.bash "
xterm -e " rosrun pick_objects pick_objects " &
