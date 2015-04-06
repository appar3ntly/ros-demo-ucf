ros-demo-ucf
============
ROS workspace for testing and demoing ROS functionality for UCF robotics club.<br></br><br></br>
Note this is **NOT** the repo for competition/actual development code.  It is entirely devoted to random testing or tutorial package code.  As such, branches other than master may at times be terribly disorganized.

# Table of Contents
* [Current Contributors](#current-contributors)
* [Current Packages](#current-packages)
* [How To Get Started Breaking Everything](#quick-start)

# <a name="current-contributors"></a>Current Contributors
* Thomas Watters 
* Kenneth Richardson


# <a name="current-packages"></a>Current Packages
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
