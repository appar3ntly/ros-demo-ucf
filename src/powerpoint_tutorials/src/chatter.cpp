#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("I heard: [%s]", msg->data.c_str());	
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "listener");
	ros::NodeHandle node;

	ros::Subscriber sub = node.subscribe("chatter", 1000, chatterCallback);

	// Let ros take over, continuously execute callbacks as messages are received.
	ros::spin();

	// The above is the same as
	// while (ros::ok())
	// {
	//  	ros::spinOnce();
	// }
	return 0;
}