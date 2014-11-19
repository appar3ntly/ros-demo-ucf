cmake_minimum_required(VERSION 2.8.3)
project(powerpoint_tutorials)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  sensor_msgs
)


catkin_package()

# directories to include in the build
include_directories(
	include/powerpoint_tutorials
  ${catkin_INCLUDE_DIRS}
)

# declare executable to build and the source files required by directory
add_executable(talker src/talker.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(talker std_msgs)

# Specify libraries to link for the executable
target_link_libraries(talker ${catkin_LIBRARIES})

# Add and link the listener executable.
add_executable(listener src/chatter.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})

add_executable(move_forward src/move_forward.cpp)
target_link_libraries(move_forward ${catkin_LIBRARIES})

add_executable(stopper src/run_stopper.cpp src/Stopper.cpp)
target_link_libraries(stopper ${catkin_LIBRARIES})

add_executable(wanderer src/run_wanderer.cpp src/Wanderer.cpp)
target_link_libraries(wanderer ${catkin_LIBRARIES})
