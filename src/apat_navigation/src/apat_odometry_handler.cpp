#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <string>
#include <sstream>

std::string APAT_DIRECTIONS_TOPIC = "apat_directions";
std::string APAT_ODOMETRY_TOPIC = "apat_odometry";

std::string APAT_ODOMETRY_HANDLER_NAME = "apat_odometry_handler";

// Global publisher shared between main and subscriber's callback
ros::Publisher apat_odometry_publisher;
// Keep last position in memory
geometry_msgs::Point current_position;

void apatDirectionsCallback(const std_msgs::String::ConstPtr& msg)
{
  std::string input_direction = msg->data;

  if (input_direction != "N" && input_direction != "NE" && input_direction != "E" && input_direction != "SE" && input_direction != "S" && input_direction != "SW" && input_direction != "W" && input_direction != "NW") {
      input_direction = "NOT_ALLOWED_DIRECTION";
  }

  if (input_direction == "NOT_ALLOWED_DIRECTION") {
    return;
  }

  // Validation is OK, proceed with execution

  ROS_INFO("I got new direction: [%s]", input_direction.c_str());

  ROS_INFO("Tu sam sigurno");

  ros::Time current_time = ros::Time::now();

  if (input_direction == "N") {
    current_position.y += 1;
  }
  if (input_direction == "NE") {
    current_position.y += 1;
    current_position.x += 1;
  }
  if (input_direction == "E") {
    current_position.x += 1;
  }
  if (input_direction == "SE") {
    current_position.y -= 1;
    current_position.x += 1;
  }
  if (input_direction == "S") {
    current_position.y -= 1;
  }
  if (input_direction == "SW") {
    current_position.y -= 1;
    current_position.x -= 1;
  }
  if (input_direction == "W") {
    current_position.x -= 1;
  }
  if (input_direction == "NW") {
    current_position.y += 1;
    current_position.x -= 1;
  }

  //next, we'll publish the odometry message over ROS
  nav_msgs::Odometry odom;
  odom.header.stamp = current_time;
  odom.header.frame_id = "apat_odometry_frame";

  // set the new position
  odom.pose.pose.position = current_position;

  std::stringstream ss;
  ss << "Sent new position 2D: " << odom.pose.pose.position.x << "," << odom.pose.pose.position.y;

  ROS_INFO("%s", ss.str().c_str());

  apat_odometry_publisher.publish(odom);
}

/**
 * Handler for APAT navigation Odometry
 */
int main(int argc, char **argv)
{

  ros::init(argc, argv, APAT_ODOMETRY_HANDLER_NAME.c_str());

  ros::NodeHandle n;

  apat_odometry_publisher = n.advertise<nav_msgs::Odometry>(APAT_ODOMETRY_TOPIC.c_str(), 50);
  ros::Subscriber apat_directions_subscriber = n.subscribe(APAT_DIRECTIONS_TOPIC.c_str(), 1000, apatDirectionsCallback);

  ros::Rate loop_rate(1);

  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  // init current position
  current_position.x = 0;
  current_position.y = 0;
  current_position.z = 0;

  while (n.ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}