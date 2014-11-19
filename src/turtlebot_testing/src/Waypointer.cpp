#include "Waypointer.h"
#include "move_base_msgs/MoveBaseGoal.h"
#include "move_base_msgs/MoveBaseActionGoal.h"

Waypointer::Waypointer(Waypoint waypoint_array[], int num_waypoints, std::string action_server)
    : base_client(action_server.c_str(), true)
{
    waypoints = waypoint_array;
    waypoint_count = num_waypoints;

    fillStack();

    while (!base_client.waitForServer(ros::Duration(5.0)))
        ROS_INFO("Waiting for action server...");
}

void Waypointer::begin()
{
    while(ros::ok())
    {
        // If the stack is empty, kill the node since we can't continue.
        if (waypoint_stack.empty())
        {
            ROS_ERROR("Waypoint stack is empty! Killing node...");
            ros::shutdown();
        }

        // Get the next waypoint from the top of the stack.
        Waypoint waypoint = waypoint_stack.top();
        // Pop off the waypoint now that we are prepared to navigate to it.
        waypoint_stack.pop();

        // Build the goal message.
        ROS_INFO("Building goal message...");
        move_base_msgs::MoveBaseGoal goal = buildGoal(waypoint);

        // Publish the pose message.
        ROS_INFO("Sending goal message...");
        base_client.sendGoal(goal);

        // Wait until we have a status for the current navigation attempt.
        ROS_INFO("Waiting for navigation result...");
        base_client.waitForResult();

        // Check the result of the navigation and send diagnostics to terminal.
        if (base_client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            ROS_INFO("Movement successful!");
        else
            ROS_INFO("Movement failed!");

        // If the stack is empty, refill it and continue.
        // Allows the turtlebot to loop through waypoints.
        if (waypoint_stack.empty())
        {
            ROS_INFO("Waypoints exhausted, refilling stack...");
            fillStack();
        }
    }
}

void Waypointer::fillStack()
{
    // Push each waypoint in the waypoints array onto the stack.
    for (int i = 0; i < waypoint_count; i++)
    {
        waypoint_stack.push(waypoints[i]);
    }
}

move_base_msgs::MoveBaseGoal Waypointer::buildGoal(Waypoint waypoint)
{
    // Get the quaternion representation of the goal pose angle.
    tf::Quaternion angle_quaternion = waypoint.getQuaternion();

    // Build the goal pose message field by field.
    move_base_msgs::MoveBaseGoal goal_pose;
    goal_pose.target_pose.header.frame_id = "map";
    goal_pose.target_pose.header.stamp = ros::Time::now();
    goal_pose.target_pose.pose.position.x = waypoint.xPos;
    goal_pose.target_pose.pose.position.y = waypoint.yPos;
    goal_pose.target_pose.pose.position.z = waypoint.zPos;
    goal_pose.target_pose.pose.orientation.x = angle_quaternion.getX();
    goal_pose.target_pose.pose.orientation.y = angle_quaternion.getY();
    goal_pose.target_pose.pose.orientation.z = angle_quaternion.getZ();
    goal_pose.target_pose.pose.orientation.w = angle_quaternion.getW();

    // Return the message we built.
    return goal_pose;
}
