#include "Wanderer.h"
#include <cstdlib>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

Wanderer::Wanderer()
{
	canMoveForward = true;

	// Advertise a new publisher for simulated robot's velocity commands
	commandPub = node.advertise<geometry_msgs::Twist>("cmd_vel", 10);

	// Subscribe to the simulated robot's laser scan topic
	laserSub = node.subscribe("base_scan", 1, &Wanderer::scanCallback, this);
}

void Wanderer::startMoving()
{
	ROS_INFO("Start Moving");
	// Keep spinning the loop until user kills the node
	while (ros::ok())
	{
		if (canMoveForward)
		{
			moveForward();
			ros::Duration(0.1).sleep();
		}
		else
		{
			// Get random rotation direction, either clockwise or counter-clockwise.
			int rotationDirection = rand() % 2;
			// Get random rotation time between 0.5 and 1.5 seconds as a decimal.
			double rotateTime = 0.5 + (rand() % 1000) / 1000.0;
			// Print rotation time to INFO
			ROS_INFO_STREAM("Rotating for " << rotateTime << " seconds");
			// Set the stop time for rotation as the current time + rotation time.
			ros::Time stopTime = ros::Time::now() + ros::Duration(rotateTime);
			while(ros::Time::now() < stopTime)
			{
				rotate(rotationDirection);
				ros::Duration(0.1).sleep();
			}

			// Reset the move forward flag.  We assume the robot can now move forwards.
			canMoveForward = true;
		}
		// Process any callbacks.
		// For this robot, these are only callbacks in response to base_scan info.
		ros::spinOnce();
	}
}

// Send a velocity command.
void Wanderer::moveForward()
{
	geometry_msgs::Twist msg;
	msg.linear.x = FORWARD_SPEED_MPS;
	ROS_INFO_STREAM("Moving forward: linear.x = " << msg.linear.x);
	commandPub.publish(msg);
}

// Send a velocity command, but for rotation only.
void Wanderer::rotate(int rotationDirection)
{
	geometry_msgs::Twist msg;
	if (rotationDirection == 1)
		msg.angular.z = ROTATION_INCREMENT;
	else
		msg.angular.z = -ROTATION_INCREMENT;
	commandPub.publish(msg);
}

// Process the incoming laser message
void Wanderer::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
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
		canMoveForward = false;
	}
}





