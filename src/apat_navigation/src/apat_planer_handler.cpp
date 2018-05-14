#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/MapMetaData.h>
#include <apat_navigation/Pathr.h>
#include <iostream>	//std::cout
#include <string>	//std::string, std::getline();


std::string APAT_PLANER_TOPIC = "apat_planer";
std::string APAT_VEHICLE_RETURN_TOPIC = "apat_vehicle_return";
std::string APAT_OCCUPANCY_GRID_TOPIC = "apat_occupancy_grid";

std::string APAT_PLANER_HANDLER_NAME = "apat_planer_handler";

// Global publisher shared between main and subscriber's callback
ros::Publisher apat_planer_publisher;

// Global occupancy grid
nav_msgs::OccupancyGrid grid;

void apatOccupancyGridCallback(nav_msgs::OccupancyGrid _grid) {

    grid = _grid;
    ROS_INFO("%d %d", grid.info.width, grid.info.height);

}

void apatVehicleReturnCallback(std_msgs::String msg) {
    if (msg.data == "RETURN_PATH") {
        ROS_INFO("Pozvan return.");
        apat_navigation::Pathr pathr;
        if (grid.info.width == 0) {
            ROS_INFO("Vehicle is on (0,0).");
        } else {
            ROS_INFO("%d %d", grid.info.width, grid.info.height);
            //std::string* return_path = new std::string[4] {"N", "NE", "SW", "S"};
            std::string strarray[] = {"NE", "N", "S", ""};

            
            std::vector<std::string> strvector(strarray, strarray + 4);
            pathr.data = strvector;
            apat_planer_publisher.publish(pathr);
        }
        
    }
}

/**
 * Handler for APAT navigation Optimal Planer handler
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, APAT_PLANER_HANDLER_NAME.c_str());
  ros::NodeHandle n;

  apat_planer_publisher = n.advertise<apat_navigation::Pathr>(APAT_PLANER_TOPIC.c_str(), 50);
  ros::Subscriber apat_occupancy_grid_subscriber = n.subscribe(APAT_OCCUPANCY_GRID_TOPIC.c_str(), 1000, apatOccupancyGridCallback);
  ros::Subscriber apat_vehicle_return_subscriber = n.subscribe(APAT_VEHICLE_RETURN_TOPIC.c_str(), 1000, apatVehicleReturnCallback);


  ros::Rate loop_rate(1);


  while (n.ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}