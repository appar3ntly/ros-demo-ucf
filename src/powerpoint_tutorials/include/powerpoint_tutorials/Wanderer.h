#ifndef WANDERER_HPP
#define WANDERER_HPP

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

class Wanderer
{
public:
	// Tunable parameters
	const static double FORWARD_SPEED_MPS = 0.6;
	const static double ROTATION_INCREMENT = 1.0;
	const static double MIN_SCAN_ANGLE_RAD = -30.0/180*M_PI;
	const static double MAX_SCAN_ANGLE_RAD = +30.0/180*M_PI;
	const static float MIN_PROXIMITY_RANGE_M = 0.75;

	Wanderer();
	void startMoving();

private:
	ros::NodeHandle node;
	ros::Publisher commandPub;
	ros::Subscriber laserSub;
	bool canMoveForward;

	void moveForward();
	void rotate(int);
	void scanCallback(const sensor_msgs::LaserScan::ConstPtr&);

};

#endif