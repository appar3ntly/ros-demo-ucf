#include "ros/ros.h"
#include "Waypoint.h"
#include "Waypointer.h"
#include "geometry_msgs/PoseStamped.h"
#include "move_base_msgs/MoveBaseResult.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "waypointer_node");

    Waypoint waypoint_array[5];
    waypoint_array[4] = Waypoint(3.8, -1.84, 0, 0, 0, 0);
    waypoint_array[3] = Waypoint(2.77, 0.96, 0, 0, 0, 0);
    waypoint_array[2] = Waypoint(-2.44, 1.08, 0, 0, 0, 0);
    waypoint_array[1] = Waypoint(2.30, -4.27, 0, 0, 0, 0);
    waypoint_array[0] = Waypoint(4.67, 0.26, 0, 0, 0, 0);

    Waypointer waypointer(waypoint_array, 5);

    waypointer.begin();
    return 0;
}
