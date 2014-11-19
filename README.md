ros-demo-ucf
============
ROS workspace for testing and demoing ROS functionality for UCF robotics club.

This is an entirely informal workspace used in exploring and potentially teaching new members about ROS functionality.
As new packages are added, entries may be placed here to explain what can be found in them or for resources used in 
their development.  Expect this space to at times be a bit unorganized or without documentation of any kind :)


Currently Maintened/Contributed to By
=====================================
Thomas Watters
Kenneth Richardson


Current Packages
================

agitr
=====
Package containing selected source code from the Jason M. O'Kane book 'A Gentle Introduction to ROS'
A free web version of the book can be found at http://www.cse.sc.edu/~jokane/agitr/

my_urdf_tutorial
================
Source code from the ROS urdf tutorials at http://wiki.ros.org/urdf/Tutorials
Specifically starting from tutorial 2.1 on the aforementioned page.

powerpoint_tutorials
====================
Source code from the powerpoint tutorials found at http://u.cs.biu.ac.il/~yehoshr1/89-685/Fall2013/index.html
Contains source for most of lessons 1-3 and a solution for the roomba-like assignment described at the end of lesson 3.

testbot_description
===================
Source for ROS urdf tutorials 1.1 up to start of 2.x.
May be deleted in the near future as it doesn't contain much useful.

turtlebot_testing
=================
Various implementations intended to test ROS features using the Turtlebot platform.


How To Get Started Breaking Everything
======================================
0. FOLLOW THIS OR ELSE!

    http://wiki.ros.org/turtlebot/Tutorials/indigo/Installation
    
1. Make a new directory wherever you prefer to have your ROS workspaces.
2. cd to the newly created directory in a terminal window.
3. Type the following in the terminal

    git clone https://github.com/appar3ntly/ros-demo-ucf
    cd ros-demo-ucf
    catkin_make
  
4. Preferably (not required but it may make life easier) make your own branch to work in before jacking everything up
   and to make sure your master stays clean.  Type in terminal
   
    git branch <desired_branch_name>
    git checkout <desired_branch_name>
    
   Where <desired_branch_name> is replaced with whatever you like.
   
5. BREAK STUFF
6. If the master updates and you'd like to pull the changes into your branch(es) type
   
    git
