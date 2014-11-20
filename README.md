ros-demo-ucf
============
ROS workspace for testing and demoing ROS functionality for UCF robotics club.

# Table of Contents
* [Current Contributors](#current-contributors)
* [Current Packages](#Current Packages)
* [How To Get Started Breaking Everything](#How To Get Started Breaking Everything)

# <a name="current-contributors"></a>Current Contributors
* Thomas Watters 
* Kenneth Richardson


# <a name="current-packages"></a>Current Packages
###agitr
Package containing selected source code from the Jason M. O'Kane book 'A Gentle Introduction to ROS'
A free web version of the book can be found at http://www.cse.sc.edu/~jokane/agitr/

###my_urdf_tutorial
Source code from the ROS urdf tutorials at http://wiki.ros.org/urdf/Tutorials
Specifically starting from tutorial 2.1 on the aforementioned page.

###powerpoint_tutorials
Source code from the powerpoint tutorials found at http://u.cs.biu.ac.il/~yehoshr1/89-685/Fall2013/index.html
Contains source for most of lessons 1-3 and a solution for the roomba-like assignment described at the end of lesson 3.

###testbot_description
Source for ROS urdf tutorials 1.1 up to start of 2.x.
May be deleted in the near future as it doesn't contain much useful.

###turtlebot_testing
Various implementations intended to test ROS features using the Turtlebot platform.


# <a name="quick-start"></a>How To Get Started Breaking Everything
0. FOLLOW THIS OR ELSE!

    http://wiki.ros.org/turtlebot/Tutorials/indigo/Installation
    
1. Make a new directory wherever you prefer to have your ROS workspaces.
2. cd to the newly created directory in a terminal window.
3. Type the following in the terminal

    ```
    git clone https://github.com/appar3ntly/ros-demo-ucf
    cd ros-demo-ucf
    catkin_make
    ```
   
4. Preferably (not required but it may make life easier) to avoid jacking up your master branch. 
Type in terminal:

    ```
    git branch <desired_branch_name>
    git checkout <desired_branch_name>
    ```

5. BREAK STUFF
