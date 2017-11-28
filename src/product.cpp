#include <ros/ros.h>
#include "std_msgs/String.h"
#include <iostream>
#include <ros/publisher.h>
#include "get/SendGoalArray.h"
void warnEmpty();
void warnWrong();
int main(int argc, char **argv) {

  ros::init(argc, argv, "product_node");
  if(argc < 2) {
    warnEmpty();
    return -1;
  }
  if (argv[1] != "CocaCola"
    || argv[1] != "Fanta"
    || argv[1] != "Qr"
    || argv[1] != "Lays") {
      warnWrong();
      return -1;
    }

  ros::NodeHandle n;

  std::cout << "_________________" << std::endl;
  std::cout << "Sending vehicle to: " << argv[1] << std::endl;
  std::cout << "_________________" << std::endl;

  ros::ServiceClient client = n.serviceClient<get::SendGoalArray>("SendGoalArray");
  get::SendGoalArray srv;
  srv.request.productName = argv[1];
  if (client.call(srv)) {
    std::cout<<"_________________"<<std::endl;

    for(int i=0;i<srv.response.size;i++)
    std::cout<<srv.response.Boxes[i]<<" boxes: "<<srv.response.BoxCounter[i]<<std::endl;

    std::cout<<"_________________"<<std::endl;

    ROS_INFO("Success");
  } else {
    ROS_ERROR("There were complications that could not been resolved ");
    return 1;
  }

  return 0;
}
void warnWrong() {
  ROS_WARN("Wrong product given.");
  ROS_WARN("<product> can be:");
  ROS_WARN(" - CocaCola");
  ROS_WARN(" - Fanta");
  ROS_WARN(" - Lays");
  ROS_WARN(" - Qr");
  ROS_WARN(" ");
}
void warnEmpty() {
  ROS_WARN("No product given.");
  ROS_WARN("rosrun get product <product>");
  ROS_WARN(" ");
  ROS_WARN("Where <product> can be:");
  ROS_WARN(" - CocaCola");
  ROS_WARN(" - Fanta");
  ROS_WARN(" - Lays");
  ROS_WARN(" - Qr");
  ROS_WARN(" ");
}
