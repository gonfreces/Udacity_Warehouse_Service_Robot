#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float64.h>
#include <add_markers/ReachGoal.h>
#include <boost/bind.hpp>
//#include <node_handle.h>
//#include "geometry_msgs/Twist.h"

//class cube
//{
	
//	public:
		
		/*cube()
			{
			
				ROS_INFO("Ready to transport cube");	
				service = n.advertiseService("/add_markers/transport_cube", &cube::handle_transport_request, this);
				

			}*/

		bool handle_transport_request(ros::NodeHandle &n, add_markers::ReachGoal::Request &req, add_markers::ReachGoal::Response &res)
			{
				ROS_INFO("in callback");
				//ros::Rate r(1);
					
 				ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
				uint32_t shape = visualization_msgs::Marker::CUBE;

  		//	while (ros::ok())
  			//{
   				 visualization_msgs::Marker marker;
   				 // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    			 marker.header.frame_id = "/robot_footprint";
			   	 marker.header.stamp = ros::Time::now();

  			  // Set the namespace and id for this marker.  This serves to create a unique ID
 		 	    // Any marker sent with the same namespace and id will overwrite the old one
			    marker.ns = "basic_shapes";
    			marker.id = 0;

    			// Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    			marker.type = shape;
	
    			// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    			marker.action = visualization_msgs::Marker::ADD;
		
					// Pickup zone marker
    			// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    			marker.pose.position.x = 0.1;
					marker.pose.position.y = 0.1;
					marker.pose.position.z = 0;
					marker.pose.orientation.x = 0.0;
					marker.pose.orientation.y = 0.0;
					marker.pose.orientation.z = 0.0;
					marker.pose.orientation.w = 1.0;

					// Set the scale of the marker -- 1x1x1 here means 1m on a side
					marker.scale.x = 0.1;
					marker.scale.y = 0.1;
					marker.scale.z = 0.1;

					// Set the color -- be sure to set alpha to something non-zero!
					marker.color.r = 0.0f;
					marker.color.g = 1.0f;
					marker.color.b = 0.0f;
					marker.color.a = 1.0;

					marker.lifetime = ros::Duration();

					/* Publish the marker
					while (marker_pub.getNumSubscribers() < 1)
					{
						if (!ros::ok())
						{
						  return 0;
						}
						ROS_WARN_ONCE("Please create a subscriber to the marker");
						sleep(1);
					}*/
					// Pick-up zone
					ROS_INFO("Pickup Zone");
    			marker_pub.publish(marker);
	
					// Pause for 5s
					ros::Duration(2.0).sleep();
	
					// Disappear
					ROS_INFO("Disappear");
					marker.color.a = 0.0;
					marker_pub.publish(marker);

					// Pause for 5s
					ros::Duration(2.0).sleep(); 

					// Drop-off zone 
					ROS_INFO("Drop-off Zone");
					marker.color.a = 1.0; // Make it visible
					marker.pose.position.x = 1; // Change the position
  			  marker.pose.position.y = 1;
					marker.lifetime = ros::Duration(); // Necessary to publish the marker
  			  marker_pub.publish(marker);
				
					ros::Duration(2.0).sleep();

  			 //	r.sleep();
         	

  		//	}
				return true;
			}

	//private:
		//ros::NodeHandle n;
		//ros::Publisher marker_pub;
		//ros::ServiceServer service;
		//visualization_msgs::Marker marker;
//};

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_p1_class");
  ros::NodeHandle n;
	//cube cb;
  //ros::Rate r(1);
  //ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
	//ros::Subscriber  = n.subscribe("/topic_name", queue_size, callback_function);
	//ros::ServiceServer service = n.advertiseService("/add_markers/transport_cube", &cube::handle_transport_request, &cb);
	ros::ServiceServer service = n.advertiseService<add_markers::ReachGoal::Request, add_markers::ReachGoal::Response>("/add_markers/transport_cube", boost::bind(&handle_transport_request, boost::ref(n), (add_markers::ReachGoal::Request &) _1, (add_markers::ReachGoal::Response &) _2));
  //ROS_INFO("Ready to send joint commands");
	//ros::init(argc, argv, "add_markers");
	//cube cb;
	ROS_INFO("Start the robot");
  ros::spin();
	return 0;
}

