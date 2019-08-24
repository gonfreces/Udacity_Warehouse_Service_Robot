#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <time.h>
#include <add_markers/ReachGoal.h>

class pick
{  
	public:
		pick()
			{
				//Define client
			  client = n.serviceClient<add_markers::ReachGoal>("/add_markers/transport_cube");			
		
				//tell the action client that we want to spin a thread by default
  			MoveBaseClient ac("move_base", true);
 
  			//wait for the action server to come up
  			while(!ac.waitForServer(ros::Duration(5.0)))
				{
	  			ROS_INFO("Waiting for the move_base action server to come up");
  			}
 
  			move_base_msgs::MoveBaseGoal goal;
				add_markers::ReachGoal rg;
 
			  //we'll send a goal to the robot to move 1 meter forward
			  goal.target_pose.header.frame_id = "robot_footprint";
			  goal.target_pose.header.stamp = ros::Time::now();
 
				goal.target_pose.pose.position.x = 1.0;
			  goal.target_pose.pose.orientation.w = 1.0;
	 
			  ROS_INFO("Sending goal 1");
			  ac.sendGoal(goal);
 
			  ac.waitForResult();
 
			  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
				{
			    ROS_INFO("Reach Goal 1");
					rg.request.msg_sent = "Pickup";
					if (!client.call(rg))
					{	
        		ROS_ERROR("Failed to call service drive_robot");
					}
				
					// Give time for robto to move and complete the on-going action
					ros::Duration(3).sleep();
					//sleep(2000);
		
					goal.target_pose.header.frame_id = "robot_footprint";
				  goal.target_pose.header.stamp = ros::Time::now();
 
					goal.target_pose.pose.position.x = 2.0;
					// goal.target_pose.pose.position.y = 0.5;
				  goal.target_pose.pose.orientation.w = 1.0;
 
				  ROS_INFO("Sending goal 2");
				  ac.sendGoal(goal);
 
				  ac.waitForResult();
 
				  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
				     ROS_INFO("Reach Goal 2");
						 rg.request.msg_sent = "Dropoff";
						 if (!client.call(rg))
						 {	
        			 ROS_ERROR("Failed to call service drive_robot");
						 }
				
					   // Give time for robto to move and complete the on-going action
					   ros::Duration(3).sleep();
					}			
				  else
					{		
				     ROS_INFO("The base failed to move forward 1 meter for some reasons");
					}
				}		
  			else
				{
    			ROS_INFO("The base failed to move forward 1 meter for some reason");
				}
			}
	private:
		ros::NodeHandle n;
		ros::ServiceClient client;
		typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
		
};	
		
 
int main(int argc, char** argv)
{
	ros::init(argc, argv, "pick_objects");
 	pick pk; 
	ROS_INFO("Run the robot");
	return 0;
}
