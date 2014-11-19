#include "Waypoint.h"

Waypoint::Waypoint()
{
    xPos = 0;
    yPos = 0;
    zPos = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;
}

Waypoint::Waypoint(double xPos, double yPos, double zPos,
                   double roll, double pitch, double yaw)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->zPos = zPos;
    this->roll = roll;
    this->pitch = pitch;
    this->yaw = yaw;
}

tf::Quaternion Waypoint::getQuaternion()
{
    return tf::Quaternion(yaw, pitch, roll);
}
