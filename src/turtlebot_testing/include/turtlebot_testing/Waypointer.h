#ifndef WAYPOINTER_H
#define WAYPOINTER_H

#include <stack>
#include <string>
#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseResult.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "Waypoint.h"

class Waypointer
{
    // Typedef for convenience when dealing with the action client code.
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

public:
    // Constructor taking array of waypoints and the size of said array.
    Waypointer(Waypoint waypoint_array[], int num_waypoints, std::string action_server = "move_base");
    // Function that starts waypoint management.
    void begin();

private:
    int waypoint_count;
    Waypoint* waypoints;
    std::stack<Waypoint> waypoint_stack;
    MoveBaseClient base_client;

    void fillStack();
    move_base_msgs::MoveBaseGoal buildGoal(Waypoint waypoint);
};

#endif
