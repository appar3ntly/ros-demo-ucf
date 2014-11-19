#include "Wanderer.h"

int main(int argc, char** argv)
{
	// Initialize a new node named wanderer.
	ros::init(argc, argv, "wanderer");

	// Create a new Wanderer object.
	Wanderer wanderer;

	// Start the wanderer moving.
	wanderer.startMoving();

	return 0;
}