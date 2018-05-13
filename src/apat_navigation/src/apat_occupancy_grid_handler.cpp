#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/MapMetaData.h>
#include <iostream>	//std::cout
#include <string>	//std::string, std::getline();
#include <stdint.h>

#include <sstream>

//#include "quadtree.h"

std::string APAT_ODOMETRY_TOPIC = "apat_odometry";
std::string APAT_OCCUPANCY_GRID_TOPIC = "apat_occupancy_grid";

// Keep it even because initial position should be in the middle with positive integer coordinates
const uint GRID_WIDTH = 20;
const uint GRID_HEIGHT = 20;

std::string APAT_OCCUPANCY_GRID_HANDLER_NAME = "apat_occupancy_grid_handler";

// Global publisher shared between main and subscriber's callback
ros::Publisher apat_occupancy_grid_publisher;
// Keep occupancy grid in memory
nav_msgs::OccupancyGrid grid;

void apatOdometryCallback(nav_msgs::Odometry odom) {
  std::stringstream ss;
  ss << "Received new position 2D: " << odom.pose.pose.position.x << "," << odom.pose.pose.position.y;
  ROS_INFO("%s", ss.str().c_str());

  // Received position is from coordinate system where the middle is (0,0)
  // grid is has the middle in the point (GRID_WIDTH/2, GRID_HEIGHT/2)
  
  // 1. convert the point to the grid position
  odom.pose.pose.position.x = (int)odom.pose.pose.position.x + GRID_WIDTH/2;
  odom.pose.pose.position.y = (int)odom.pose.pose.position.y + GRID_HEIGHT/2;

  // 2. Set new position as origin in the grid
  grid.info.origin = odom.pose.pose;

  // 3. Set the cell is taken
  grid.data[(int)grid.info.origin.position.x + grid.info.width * (int)grid.info.origin.position.y] = 1;

  // 4. Print the grid
  std::string y = "";
  for (int i = 0; i < grid.info.width; i++) {
    y = "";
    for (int j = 0; j < grid.info.height; j++) {      
      if (grid.data[i + grid.info.width * j] == 0) {
        y.push_back('0');
      } else {
        y.push_back('1');
      }      
    }
    ROS_INFO("%s", y.c_str());
  }

}

/**
 * Handler for APAT navigation Occupancy grid handler
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, APAT_OCCUPANCY_GRID_HANDLER_NAME.c_str());
  ros::NodeHandle n;

  apat_occupancy_grid_publisher = n.advertise<nav_msgs::OccupancyGrid>(APAT_OCCUPANCY_GRID_TOPIC.c_str(), 50);
  ros::Subscriber apat_directions_subscriber = n.subscribe(APAT_ODOMETRY_TOPIC.c_str(), 1000, apatOdometryCallback);

  ros::Rate loop_rate(1);

  // Init grid
  nav_msgs::MapMetaData info;
  info.resolution = 1;
  info.width = GRID_WIDTH;
  info.height = GRID_HEIGHT;
  // Initial position in the middle of the grid
  // This is the simulaton for infinity 2D coordinate system
  info.origin.position.x = info.width / 2;
  info.origin.position.y = info.height / 2;

  // Init all cells to empty
  // 0 is empty (free = not visited by vehicle simulator)
  // 1 is taken (visited by vehicle simulator)
  signed char p[info.width * info.height] = {0};

  for (int i = 0; i < info.width; i++) {
    for (int j = 0; j < info.height; j++) {
      p[i + info.width * j] = 0;
    }
  }
  ROS_INFO("Got map %d %d", info.width, info.height);
  std::vector<signed char> a(p, p+(info.width*info.height)); 
  grid.data = a;

  // Mark initial position as taken in the grid
  grid.data[(int)info.origin.position.x + info.width * (int)info.origin.position.y] = 1;

  std::string y("");
  
  for (int i = 0; i < info.width; i++) {
    y = "";
    for (int j = 0; j < info.height; j++) {      
      if (grid.data[i + info.width * j] == 0) {
        y.push_back('0');
      } else {
        y.push_back('1');
      }      
    }
    ROS_INFO("%s", y.c_str());
  }
  
  ROS_INFO("Initial position (%d,%d)", (int)info.origin.position.x, (int)info.origin.position.y);

  grid.info = info;

  while (n.ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;

}