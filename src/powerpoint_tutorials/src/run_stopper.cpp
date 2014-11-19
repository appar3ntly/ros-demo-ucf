#include "Stopper.h"
#include "ros/ros.h"

int main(int argc, char** argv)
{
	// Initiate a new ros node named "stopper"
	ros::init(argc, argv, "stopper");

	// Create a new Stopper object
	Stopper stopper;

	// Start the movement.
	stopper.startMoving();
	
	return 0;
}