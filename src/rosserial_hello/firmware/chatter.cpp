#include <ros.h>
#include <std_msgs/String.h>

#include <Arduino.h>

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char error_msg[] = "command not recognized! please use toggle";
char hello[] = "hello world!";

void special_callback(const std_msgs::String& incoming_msg)
{
	String data(incoming_msg.data);
	if (data == "toggle")
		digitalWrite(13, HIGH-digitalRead(13));
	else
	{
		str_msg.data = error_msg;
		chatter.publish(&str_msg);
		str_msg.data = incoming_msg.data;
		chatter.publish(&str_msg);
	}
}

ros::Subscriber<std_msgs::String> sub("incoming_msg", &special_callback);

void setup()
{
	pinMode(13, OUTPUT);
	nh.initNode();
	nh.advertise(chatter);
	nh.subscribe(sub);
}

void loop()
{
	str_msg.data = hello;
	chatter.publish(&str_msg);
	nh.spinOnce();
	delay(1000);
}