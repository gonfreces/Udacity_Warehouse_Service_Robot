#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <time.h>
 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
 
int main(int argc, char** argv){
	ros::init(argc, argv, "pick_objects");
 
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
 
  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
	  ROS_INFO("Waiting for the move_base action server to come up");
  }
 
  move_base_msgs::MoveBaseGoal goal;
 
  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "robot_footprint";
  goal.target_pose.header.stamp = ros::Time::now();
 
	goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.orientation.w = 1.0;
 
  ROS_INFO("Sending goal 1");
  ac.sendGoal(goal);
 
  ac.waitForResult();
 
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Reach Goal 1");
		
		sleep(5000);

		goal.target_pose.header.frame_id = "robot_footprint";
	  goal.target_pose.header.stamp = ros::Time::now();
 
		goal.target_pose.pose.position.x = 3.0;
		goal.target_pose.pose.position.x = 0.5;
	  goal.target_pose.pose.orientation.w = 0.0;
 
	  ROS_INFO("Sending goal 2");
	  ac.sendGoal(goal);
 
	  ac.waitForResult();
 
	  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	     ROS_INFO("Reach Goal 2");
	  else
	     ROS_INFO("The base failed to move forward 1 meter for some reasons");
	}		
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");

	return 0;
}
