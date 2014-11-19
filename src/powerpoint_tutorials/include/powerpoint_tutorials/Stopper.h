#ifndef STOPPER_HPP
#define STOPPER_HPP

//#ifndef STOPPER_H
//#define STOPPER_H

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

class Stopper
{
public:
	// Tunable parameters
	const static double FORWARD_SPEED_MPS = 0.2;
	const static double MIN_SCAN_ANGLE_RAD = -30.0/180*M_PI;
	const static double MAX_SCAN_ANGLE_RAD = +30.0/180*M_PI;
	const static float MIN_PROXIMITY_RANGE_M = 0.5;

	Stopper();
	void startMoving();

private:
	ros::NodeHandle node;  // NodeHandle for setting up publisher/subscriber links, etc.
	ros::Publisher commandPub;  // Publisher to the velocity command topic.
	ros::Subscriber laserSub;  // Subscriber to the laser scan messages.
	bool keepMoving;  // Indicates whether we can continue moving forward without collision.

	void moveForward();
	void scanCallback(const sensor_msgs::LaserScan::ConstPtr&);
};

#endif