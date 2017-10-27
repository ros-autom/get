#include <ros/ros.h>
#include "std_msgs/String.h"
#include <iostream>
#include <ros/publisher.h>
#include "get/SendGoalArray.h"
int main(int argc, char **argv) {
  ros::init(argc, argv, "product_node");

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
