cmake_minimum_required(VERSION 2.8.3)
project(openpose_ros)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  cv_bridge
  sensor_msgs
  image_recognition_msgs
)

catkin_package()

# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  /usr/local/cuda-8.0/include
  /home/iqit/openpose/include
  /home/iqit/openpose/3rdparty/caffe/include
  /home/iqit/openpose/3rdparty/caffe/.build_release/src
)

add_executable(openpose_ros_node src/openpose_ros_node.cpp)

add_executable(openpose_ros_client src/openpose_ros_client.cpp)


# Specify libraries to link a library or executable target against
target_link_libraries(openpose_ros_node
  ${catkin_LIBRARIES}
  /home/iqit/openpose/build/lib/libopenpose.so
  /home/iqit/openpose/3rdparty/caffe/.build_release/lib/libcaffe.so
)

# Specify libraries to link a library or executable target against
target_link_libraries(openpose_ros_client
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)


