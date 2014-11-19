#include "Stopper.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

Stopper::Stopper()
{
	keepMoving = true;

	// Advertise a new publisher for simulated robot's velocity commands
	commandPub = node.advertise<geometry_msgs::Twist>("cmd_vel", 10);

	// Subscribe to the simulated robot's laser scan topic
	laserSub = node.subscribe("base_scan", 1, &Stopper::scanCallback, this);
}

void Stopper::startMoving()
{
	ros::Rate rate(10);
	ROS_INFO("Start Moving");

	// Keep spinning the loop until user kills the node or robot gets too close to an obstacle
	while (ros::ok() && keepMoving)
	{
		moveForward();
		ros::spinOnce();
		rate.sleep();
	}
}

// Send a velocity command.
void Stopper::moveForward()
{
	geometry_msgs::Twist msg;
	msg.linear.x = FORWARD_SPEED_MPS;
	commandPub.publish(msg);
}

// Process the incoming laser message
void Stopper::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
	// Find the closest range between the defined minimum and maximum angles.
	int minIndex = ceil((MIN_SCAN_ANGLE_RAD - scan->angle_min) / scan->angle_increment);
	int maxIndex = floor((MAX_SCAN_ANGLE_RAD - scan->angle_min) / scan->angle_increment);

	float closestRange = scan->ranges[minIndex];
	for (int currentIndex = minIndex + 1; currentIndex <= maxIndex; currentIndex++)
	{
		if (scan->ranges[currentIndex] < closestRange)
		{
			closestRange = scan->ranges[currentIndex];
		}
	}

	ROS_INFO_STREAM("Closest range: " << closestRange);

	if (closestRange < MIN_PROXIMITY_RANGE_M)
	{
		ROS_INFO("Stop!");
		keepMoving = false;
	}
}		
