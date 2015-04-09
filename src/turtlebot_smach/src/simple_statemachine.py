#!/usr/bin/env python
import rospy
import smach
import smach_ros
from actionlib import *
from actionlib_msgs.msg import *
from geometry_msgs.msg import PoseStamped
from move_base_msgs.msg import MoveBaseAction
from move_base_msgs.msg import MoveBaseGoal
from move_base_msgs.msg import MoveBaseResult
from move_base_msgs.msg import MoveBaseActionResult
from smach_ros import ServiceState
from smach_ros import SimpleActionState
from std_srvs.srv import Empty
from waypoint_manager_msgs.srv import NextWaypoint
from waypoint_manager_msgs.srv import PushWaypoint


class Idle(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['succeeded'])

    def execute(self, userdata):
        rospy.wait_for_service('advance_waypoint')
        rospy.wait_for_service('backtrack_waypoint')
        rospy.wait_for_service('next_waypoint')
        rospy.wait_for_service('push_new_waypoint')
        return 'succeeded'


class GetNextWaypoint(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['succeeded', 'aborted'], output_keys=['waypoint_out'])

    def execute(self, userdata):
        try:
            get_waypoint_proxy = rospy.ServiceProxy('next_waypoint', NextWaypoint)
            waypoint_response = get_waypoint_proxy()
            userdata.waypoint_out = waypoint_response.waypoint
        except rospy.ServiceException:
            return 'aborted'

        return 'succeeded'


class MovingToWaypoint(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['succeeded', 'failed'], input_keys=['waypoint_in'])

    def execute(self, userdata):
        rospy.loginfo("In MovingToWaypoint")
        move_base_client = SimpleActionClient('move_base', MoveBaseAction)
        move_base_client.wait_for_server(rospy.Duration(5))
        goal_pose = MoveBaseGoal()
        goal_pose.target_pose.header.frame_id = 'map'
        goal_pose.target_pose.header.stamp = rospy.Time.now()
        goal_pose.target_pose.pose = userdata.waypoint_in
        move_base_client.send_goal(goal_pose)
        move_base_client.wait_for_result()
        result = move_base_client.get_state()
        if (result == GoalStatus.SUCCEEDED):
            return 'succeeded'
        else:
            return 'failed'


class AdvanceWaypoint(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['succeeded'])

    def execute(self, userdata):
        rospy.loginfo("In AdvanceWaypoint")
        advance_waypoint_proxy = rospy.ServiceProxy('advance_waypoint', Empty)
        advance_waypoint_proxy()
        return 'succeeded'


class BacktrackWaypoint(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['succeeded'])

    def execute(self, userdata):
        backtrack_waypoint_proxy = rospy.ServiceProxy('backtrack_waypoint', Empty)
        backtrack_waypoint_proxy()
        return 'succeeded'


def main():
    rospy.init_node('test_state_machine')

    # Create the state machine
    sm = smach.StateMachine(outcomes=['finish'])

    # Open top level state machine
    with sm:
        # Add intial idle state.
        smach.StateMachine.add("Idle", Idle(), transitions={'succeeded':'GetNextWaypoint'})

        # Add GetNextWaypoint state.
        smach.StateMachine.add("GetNextWaypoint", GetNextWaypoint(),
                               transitions={'succeeded':'MovingToWaypoint',
                                            'aborted':'finish'},
                               remapping={'waypoint_out':'waypoint_in'})

        # Add MovingToWaypoint state.
        smach.StateMachine.add("MovingToWaypoint", MovingToWaypoint(),
                               transitions={'succeeded':'AdvanceWaypoint',
                                            'failed':'finish'})

        # Add AdvanceWaypoint state.
        smach.StateMachine.add("AdvanceWaypoint", AdvanceWaypoint(),
                               transitions={'succeeded':'GetNextWaypoint'})

    sis = smach_ros.IntrospectionServer('state_server', sm, '/SM')
    sis.start()

    outcome = sm.execute()

    rospy.spin()
    sis.stop()


if __name__ == '__main__':
    main()
