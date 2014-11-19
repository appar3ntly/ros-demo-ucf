#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "ros/ros.h"
#include "tf/tf.h"

class Waypoint
{
public:
    // All fields stored by the Waypoint class.
    // Exposed as public instead of providing accessors.
    double xPos, yPos, zPos, roll, pitch, yaw;

    // Default constructor.
    Waypoint();

    // Construct waypoint object with all information.
    Waypoint(double xPos, double yPos, double zPos,
                       double roll, double pitch, double yaw);

    // Wrapper for getting Quaternion representation of the angle.
    tf::Quaternion getQuaternion();

private:

};

#endif
