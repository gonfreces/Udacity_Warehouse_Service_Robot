#!/bin/sh
xterm -e " gazebo " &
sleep 5
xterm -e " source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5
xterm -e " cd catkin_ws/"
xterm -e " source devel/setup.bash"
xterm -e " rosrun rviz rviz"
