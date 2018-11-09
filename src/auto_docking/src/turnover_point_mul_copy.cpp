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
  goal_0.target_pose.pose.position.x = -0.452; //1.371;
  goal_0.target_pose.pose.position.y = -0.437;//-3.225;
	
  goal_0.target_pose.pose.orientation.x = 0.0;
  goal_0.target_pose.pose.orientation.y = 0.0;
  goal_0.target_pose.pose.orientation.z = -0.164;//0.562;
  goal_0.target_pose.pose.orientation.w = 0.986;//0.827;


  move_base_msgs::MoveBaseGoal goal_1;

  goal_1.target_pose.header.frame_id = "map";
  goal_1.target_pose.header.stamp = ros::Time::now();
  goal_1.target_pose.pose.position.x = -0.51; //1.371;
  goal_1.target_pose.pose.position.y = -0.334;//-3.225;
	
  goal_1.target_pose.pose.orientation.x = 0.0;
  goal_1.target_pose.pose.orientation.y = 0.0;
  goal_1.target_pose.pose.orientation.z = -0.152;//0.562;
  goal_1.target_pose.pose.orientation.w = 0.988;//0.827;

	move_base_msgs::MoveBaseGoal goal_2;
  goal_2.target_pose.header.frame_id = "map";
  goal_2.target_pose.header.stamp = ros::Time::now();
  goal_2.target_pose.pose.position.x = -0.582; 
  goal_2.target_pose.pose.position.y = -0.359;
  
  goal_2.target_pose.pose.orientation.x = 0.0;
  goal_2.target_pose.pose.orientation.y = 0.0;
  goal_2.target_pose.pose.orientation.z = -0.152;
  goal_2.target_pose.pose.orientation.w = 0.988;

//  move_base_msgs::MoveBaseGoal goal_3;
//  goal_3.target_pose.header.frame_id = "map";
//  goal_3.target_pose.header.stamp = ros::Time::now();
//  goal_3.target_pose.pose.position.x = -0.477; 
//  goal_3.target_pose.pose.position.y = -0.438;
  
//  goal_3.target_pose.pose.orientation.x = 0.0;
//  goal_3.target_pose.pose.orientation.y = 0.0;
//  goal_3.target_pose.pose.orientation.z = -0.148;
//  goal_3.target_pose.pose.orientation.w = 0.988;
  
//  move_base_msgs::MoveBaseGoal goal_4;
//  goal_4.target_pose.header.frame_id = "map";
//  goal_4.target_pose.header.stamp = ros::Time::now();
//  goal_4.target_pose.pose.position.x = -0.61; 
//  goal_4.target_pose.pose.position.y = -0.367;
  
//  goal_4.target_pose.pose.orientation.x = 0.0;
//  goal_4.target_pose.pose.orientation.y = 0.0;
//  goal_4.target_pose.pose.orientation.z = -0.147;
//  goal_4.target_pose.pose.orientation.w = 0.989;

  std::string aa("goto_turnover_point_0");
  std::string bb("goto_turnover_point_1");
  std::string cc("goto_turnover_point_2");
//  std::string dd("goto_turnover_point_3");
//  std::string ee("goto_turnover_point_4");


	if (msg->data.c_str() == aa)
    ac.sendGoal(goal_0);
  else if(msg->data.c_str() == bb)
    ac.sendGoal(goal_1);
  else if(msg->data.c_str() == cc)
    ac.sendGoal(goal_2);
//  else if(msg->data.c_str() == dd)
//    ac.sendGoal(goal_3);
//  else if(msg->data.c_str() == ee)
//    ac.sendGoal(goal_4);
  else
    return;

}
int main(int argc, char** argv){
  ros::init(argc, argv, "turnover_point_mul");
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
