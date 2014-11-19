#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
	const double FORWARD_SPEED_MPS = 0.2;

	// Initialize node "move_forward"
	ros::init(argc, argv, "move_forward");
	ros::NodeHandle node;

	// Hook up as publisher on topic cmd_vel
	ros::Publisher pub = node.advertise<geometry_msgs::Twist>("cmd_vel", 10);

	// Create a new geometry_msg::Twist, set linear.x to FORWARD_SPEED_MPS
	geometry_msgs::Twist msg;
	msg.linear.x = FORWARD_SPEED_MPS;
	msg.angular.z = FORWARD_SPEED_MPS;

	// loop at 10 Hz
	ros::Rate rate(10);
	ROS_INFO("Starting to move forward");
	while (ros::ok())
	{
		pub.publish(msg);
		rate.sleep();
	}
}