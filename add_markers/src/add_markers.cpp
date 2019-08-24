#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float64.h>
#include <add_markers/ReachGoal.h>

class cube
{
	public:
		/*marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

		uint32_t shape = visualization_msgs::Marker::CUBE;

		visualization_msgs::Marker marker;*/
				
		cube()
			{
				marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

				uint32_t shape = visualization_msgs::Marker::CUBE;

				visualization_msgs::Marker marker;

    		marker.header.frame_id = "/robot_footprint";
  			marker.header.stamp = ros::Time::now();

   			//marker.ns = "basic_shapes";
  			//marker.id = 0;

			  marker.type = shape;

			  marker.action = visualization_msgs::Marker::ADD;
		
			  marker.pose.position.x = 0.1;
			  marker.pose.position.y = 0.1;
			  marker.pose.position.z = 0;
			  marker.pose.orientation.x = 0.0;
			  marker.pose.orientation.y = 0.0;
			  marker.pose.orientation.z = 0.0;
 				marker.pose.orientation.w = 1.0;

			  marker.scale.x = 0.1;
			  marker.scale.y = 0.1;
			  marker.scale.z = 0.1;

			  marker.color.r = 0.0f;
			  marker.color.g = 1.0f;
			  marker.color.b = 0.0f;
			  marker.color.a = 1.0;

			  marker.lifetime = ros::Duration();	
				ROS_INFO("Cube ready");
				marker_pub.publish(marker);

				service = n.advertiseService("/add_markers/transport_cube", &cube::handle_transport_request, this);
				ROS_INFO("Ready to transport cube");	

			}

		bool handle_transport_request(add_markers::ReachGoal::Request& req, add_markers::ReachGoal::Response& res)
			{
				//S s = "ReachGoal request received " + req.msg_sent;
				//ROS_INFO_STREAM(s);
				ROS_INFO_STREAM("ReachGoal request received "<< req.msg_sent);
		
				if (req.msg_sent == "Pickup")
				{
					ROS_INFO("Pickup Zone");
    			marker_pub.publish(marker);
					res.msg_feedback = "Pickup Cube Successful";
					ROS_INFO_STREAM(res.msg_feedback);
				
					ROS_INFO("Disappear");
					marker.color.a = 0.0;
					marker.lifetime = ros::Duration();
					marker_pub.publish(marker);
				}
				else if (req.msg_sent == "Dropoff")
				{
					ROS_INFO("Dropoff Zone");
					marker.color.a = 1.0; // Make it visible
					marker.pose.position.x = 1; // Change the position
    			marker.pose.position.y = 1;
					marker.lifetime = ros::Duration(); // Necessary to publish the marker
     			marker_pub.publish(marker);
					res.msg_feedback = "Dropoff Cube Successful";
					ROS_INFO_STREAM(res.msg_feedback);
				}
				return true;
			}

	private:
		ros::NodeHandle n;
		ros::Publisher marker_pub;
		ros::ServiceServer service;
		visualization_msgs::Marker marker;
};

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
	cube cb;
	ROS_INFO("Start the robot");
  ros::spin();
	return 0;
}
