#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char** argv)
{
	// Initialize this node with name "talker"
	ros::init(argc, argv, "talker");

	// Create the NodeHandle object for this node
	ros::NodeHandle nh;

	// Create a publisher to advertise on topic "chatter" with queue size 1000.
	ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

	// Set the loop running rate to 10 Hz
	ros::Rate loop_rate(10);

	int count = 0;
	while (ros::ok())
	{
		// Create a new std_msgs::String
		std_msgs::String msg;

		// Create a new stringstream
		std::stringstream ss;

		// Push "hello world " and count into the stringstream
		ss << "hello world " << count;

		// Set the data field of msg to the string in ss
		msg.data = ss.str();

		// Macro for printing 
		ROS_INFO("%s", msg.data.c_str());

		// Publish the message msg on the topic
		chatter_pub.publish(msg);

		// Process the frontmost callback function on the callback queue.
		ros::spinOnce();

		// Sleep for however long is necessary to maintain 10 Hz running rate
		loop_rate.sleep();
		count++;
	}


	return 0;
}