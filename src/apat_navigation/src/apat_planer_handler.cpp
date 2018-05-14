#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/MapMetaData.h>
#include <iostream>	//std::cout
#include <string>	//std::string, std::getline();


std::string APAT_PLANER_TOPIC = "apat_planer";
std::string APAT_OCCUPANCY_GRID_TOPIC = "apat_occupancy_grid";

std::string APAT_PLANER_HANDLER_NAME = "apat_planer_handler";

// Global publisher shared between main and subscriber's callback
ros::Publisher apat_planer_publisher;


void apatOccupancyGridCallback(nav_msgs::OccupancyGrid grid) {



}

/**
 * Handler for APAT navigation Optimal Planer handler
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, APAT_PLANER_HANDLER_NAME.c_str());
  ros::NodeHandle n;

  apat_planer_publisher = n.advertise<std_msgs::String>(APAT_PLANER_TOPIC.c_str(), 50);
  ros::Subscriber apat_occupancy_grid_subscriber = n.subscribe(APAT_OCCUPANCY_GRID_TOPIC.c_str(), 1000, apatOccupancyGridCallback);

  ros::Rate loop_rate(1);


  while (n.ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}