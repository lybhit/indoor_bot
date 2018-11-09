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
  
        move_base_msgs::MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = -2.002;
	goal.target_pose.pose.position.y = 2.108;
	goal.target_pose.pose.position.z = 0.18;
	
    
	goal.target_pose.pose.orientation.x = 0.0;
	goal.target_pose.pose.orientation.y = 0.0;
	goal.target_pose.pose.orientation.z = -0.802;
	goal.target_pose.pose.orientation.w = 0.598;
	
	std::string aa("goto_turnover_point");
	if (msg->data.c_str() == aa)
	{
//          ROS_INFO("Sending goal");
          ac.sendGoal(goal);
//          ROS_INFO("Goal has been sended!");
	}
	ac.waitForResult();
}
void callback_1(const std_msgs::String::ConstPtr& msg)
   {
          MoveBaseClient ac("move_base", true);
  
          while(!ac.waitForServer(ros::Duration(1.0))){
//          ROS_INFO("Waiting for the move_base action server to come up");
    }
  
          move_base_msgs::MoveBaseGoal goal;
          goal.target_pose.header.frame_id = "map";
          goal.target_pose.header.stamp = ros::Time::now();
          goal.target_pose.pose.position.x = -1.870;
          goal.target_pose.pose.position.y = 2.246;
          goal.target_pose.pose.position.z = 0.19;
  
  
          goal.target_pose.pose.orientation.x = 0.0;
          goal.target_pose.pose.orientation.y = 0.0;
          goal.target_pose.pose.orientation.z = -0.806;
          goal.target_pose.pose.orientation.w = 0.591;
  
          std::string aa("goto_turnover_point");
          if (msg->data.c_str() == aa)
          {
//            ROS_INFO("Sending goal");
            ac.sendGoal(goal);
//            ROS_INFO("Goal has been sended!");
          }
          ac.waitForResult();
 }

int main(int argc, char** argv){
  ros::init(argc, argv, "turnover_point");
  ros::NodeHandle n;
  
  ros::Subscriber sub = n.subscribe("goto_turnover_point", 10, callback);
  ros::Subscriber sub_1 = n.subscribe("goto_turnover_point_1", 10, callback_1);

  //tell the action client that we want to spin a thread by default
  //MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  /*while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }*/
  
  ros::spin();
  
  return 0;
}
