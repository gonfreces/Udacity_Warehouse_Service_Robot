# Udacity_Warehouse_Service_Robot

### Launch

- Open a termainal window
- Go into the `catkin_ws` workspace and run `catkin_make`
- Source the environment variables - `source devel/setup.bash`
- Go into the scripts folder and then run ` ./home_service.sh `
- You can see the output in the termnal windows and rviz

### Concept

Three packages:
* my_robot - Contains all the launch files, gazebo world, AMCL paramters files, and robot urdf files
* pick_objects - Contains the 2D navigation goal setting files and the service client files
* add_markers - Contains the marker visualization and the service server files

* The actionlib gives the confirmation whether the robot has successfully reached given navigation goals and using that as the request for setting up the service to visualize the marker at the required time 
