#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <iostream>	//std::cout
#include <string>	//std::string, std::getline();

#include <sstream>

std::string APAT_ODOMETRY_TOPIC = "apat_odometry";
std::string APAT_MAP_TOPIC = "apat_map";

std::string APAT_OCCUPANCY_GRID_HANDLER_NAME = "apat_occupancy_grid_handler";

// Global publisher shared between main and subscriber's callback
ros::Publisher apat_occupancy_grid_publisher;

void apatOdometryCallback(nav_msgs::Odometry odom) {
  std::stringstream ss;
  ss << "Received new position 2D: " << odom.pose.pose.position.x << "," << odom.pose.pose.position.y;

  ROS_INFO("%s", ss.str().c_str());
}

/**
 * Handler for APAT navigation Occupancy grid handler
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, APAT_OCCUPANCY_GRID_HANDLER_NAME.c_str());
  ros::NodeHandle n;

  //apat_occupancy_grid_publisher = n.advertise<nav_msgs::Odometry>(APAT_MAP_TOPIC.c_str(), 50);
  ros::Subscriber apat_directions_subscriber = n.subscribe(APAT_ODOMETRY_TOPIC.c_str(), 1000, apatOdometryCallback);

  ros::Rate loop_rate(1);


  while (n.ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;

}