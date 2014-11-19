#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <cstdio>

int main(int argc, char **argv)
{
	const double FORWARD_SPEED_MPS = 1.0;

	// Initialize node "move_forward"
	ros::init(argc, argv, "move_forward");
	ros::NodeHandle node;

	char option;

	// Hook up as publisher on topic cmd_vel
	ros::Publisher pub = node.advertise<geometry_msgs::Twist>("cmd_vel", 10);

	// Create a new geometry_msg::Twist, set linear.x to FORWARD_SPEED_MPS
	geometry_msgs::Twist msg;

	// loop at 10 Hz
	while (ros::ok())
	{
		option = getchar();
		switch(option)
		{
			case 'w':
				msg.linear.x = FORWARD_SPEED_MPS;
				break;
			case 's':
				msg.linear.x = -FORWARD_SPEED_MPS;
				break;
			case 'a':
				msg.angular.z = FORWARD_SPEED_MPS;
				break;
			case 'd':
				msg.angular.z = -FORWARD_SPEED_MPS;
				break;
			default:
				continue;
		}
		pub.publish(msg);
		msg.linear.x = 0.0;
		msg.angular.z = 0.0;
	}
}