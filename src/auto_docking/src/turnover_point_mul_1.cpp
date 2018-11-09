#include <ros/ros.h>
#include "std_msgs/String.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void callback(const std_msgs::String::ConstPtr& msg)
{
	MoveBaseClient ac("move_base", true);
	
	while(!ac.waitForServer(ros::Duration(1.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  move_base_msgs::MoveBaseGoal goal_0;

	goal_0.target_pose.header.frame_id = "map";
  goal_0.target_pose.header.stamp = ros::Time::now();
  goal_0.target_pose.pose.position.x = 11.9; //;
	goal_0.target_pose.pose.position.y = -6.12;//;
	
	goal_0.target_pose.pose.orientation.x = 0.0;
	goal_0.target_pose.pose.orientation.y = 0.0;
	goal_0.target_pose.pose.orientation.z = 0.985;//0.562;
	goal_0.target_pose.pose.orientation.w = 0.171;//0.827;


	move_base_msgs::MoveBaseGoal goal_1;
  goal_1.target_pose.header.frame_id = "map";
  goal_1.target_pose.header.stamp = ros::Time::now();
  goal_1.target_pose.pose.position.x = 11.9; 
  goal_1.target_pose.pose.position.y = -6.17;
  
  goal_1.target_pose.pose.orientation.x = 0.0;
  goal_1.target_pose.pose.orientation.y = 0.0;
  goal_1.target_pose.pose.orientation.z = 0.985;
  goal_1.target_pose.pose.orientation.w = 0.171;

  move_base_msgs::MoveBaseGoal goal_2;
  goal_2.target_pose.header.frame_id = "map";
  goal_2.target_pose.header.stamp = ros::Time::now();
  goal_2.target_pose.pose.position.x = 11.9; 
  goal_2.target_pose.pose.position.y = -6.20;
  
  goal_2.target_pose.pose.orientation.x = 0.0;
  goal_2.target_pose.pose.orientation.y = 0.0;
  goal_2.target_pose.pose.orientation.z = 0.985;
  goal_2.target_pose.pose.orientation.w = 0.171;
  
	std::string aa("goto_turnover_point_0");
  std::string bb("goto_turnover_point_1");
  std::string cc("goto_turnover_point_2");

	if (msg->data.c_str() == aa)
    ac.sendGoal(goal_0);
  else if(msg->data.c_str() == bb)
    ac.sendGoal(goal_1);
  else if(msg->data.c_str() == cc)
    ac.sendGoal(goal_2);
  else
    return;

}
int main(int argc, char** argv){
  ros::init(argc, argv, "turnover_point_mul_1");
  ros::NodeHandle n;
  
  ros::Subscriber sub = n.subscribe("goto_turnover_point", 10, callback);

  //tell the action client that we want to spin a thread by default
  //MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  /*while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }*/
  
  ros::spin();
  
  return 0;
}
