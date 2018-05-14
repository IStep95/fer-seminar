#include "ros/ros.h"
#include "std_msgs/String.h"
#include <apat_navigation/Pathr.h>
#include <iostream>	//std::cout
#include <string>	//std::string, std::getline();

#include <sstream>

std::string APAT_DIRECTIONS_TOPIC = "apat_directions";
std::string APAT_VEHICLE_RETURN_TOPIC = "apat_vehicle_return";
std::string APAT_PLANER_TOPIC = "apat_planer";

std::string APAT_VEHICLE_SIMULATOR_NAME = "apat_vehicle_simulator";

void apatVehicleReturnCallback(apat_navigation::Pathr pathr) {

    ROS_INFO("Ruta za nazad.");
    int i = 0;
    
    while(std::strcmp(pathr.data[i].c_str(), "") != 0)
    {
        ROS_INFO("%s", pathr.data[i].c_str());
        i++;
    }
    
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, APAT_VEHICLE_SIMULATOR_NAME.c_str());
  ros::NodeHandle n;

  ros::Publisher directions_pub = n.advertise<std_msgs::String>(APAT_DIRECTIONS_TOPIC, 50);
  ros::Publisher vehicle_return_pub = n.advertise<std_msgs::String>(APAT_VEHICLE_RETURN_TOPIC, 50);
  ros::Subscriber apat_planer_subscriber = n.subscribe(APAT_PLANER_TOPIC, 1000, apatVehicleReturnCallback);
  
  ros::Rate loop_rate(1);

  std::cout << "Hello, this is the vehicle simulator." << std::endl;

  while (ros::ok() && n.ok())
  {
    std::string input_direction;

    std::cout << "Give me the next vehicle's direction (possible directions: N,NE,E,SE,S,SW,W,NW or RETURN_PATH or EXIT) = ";

    //Get a line of input and output the results
    std::getline(std::cin, input_direction);
    std::cout << "You entered: \"" << input_direction << "\"" << std::endl;

    if (input_direction == "EXIT") {
        break;
    }

    if (input_direction == "RETURN_PATH") {
        std_msgs::String msg;
        msg.data = "RETURN_PATH";

        ROS_INFO("TOPIC: '%s' MESSAGE: '%s'", APAT_VEHICLE_RETURN_TOPIC.c_str(), msg.data.c_str());
        vehicle_return_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();

    } else {

        if (input_direction != "N" && input_direction != "NE" && input_direction != "E" && input_direction != "SE" && input_direction != "S" && input_direction != "SW" && input_direction != "W" && input_direction != "NW") {
            input_direction = "NOT_ALLOWED_DIRECTION";
        }

        if (input_direction == "NOT_ALLOWED_DIRECTION") {
            std::cout << "You have give me the bad instruction for the next vehicle's direction :(" << std::endl << "Your command is ignored, please try again." << std::endl;
        } else {
            std_msgs::String msg;
            std::stringstream ss;
            ss << input_direction;
            msg.data = ss.str();

            ROS_INFO("TOPIC: '%s' MESSAGE: '%s'", APAT_DIRECTIONS_TOPIC.c_str(), msg.data.c_str());
            directions_pub.publish(msg);

            ros::spinOnce();

            loop_rate.sleep();
        }


    }

    // Better UI
    std::cout << std::endl;

  }

  return 0;
}