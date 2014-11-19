#include <urdf/model.h>
#include "ros/ros.h"

using std::string;

int main(int argc, char** argv)
{
	// Initialize a new ros node.
	ros::init(argc, argv, "my_parser");
	// If not a single command line argument, bail out.
	if (argc != 2)
	{
		ROS_ERROR("Need a urdf file as argument");
		return -1;
	}
	// Sole argument should be the urdf file filename
	string urdf_file = argv[1];

	// Create a new urdf Model object
	urdf::Model model;
	// If parsing fails, just bail out.
	if (!model.initFile(urdf_file))
	{
		ROS_ERROR("Failed to parse urdf file");
		return -1;
	}
	ROS_INFO("Successfully parsed urdf file");
	return 0;
}