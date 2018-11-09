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
        goal.target_pose.pose.position.x = -0.582; //1.371;
	goal.target_pose.pose.position.y = -0.359;//-3.225;
	
        

 
	goal.target_pose.pose.orientation.x = 0.0;
	goal.target_pose.pose.orientation.y = 0.0;
	goal.target_pose.pose.orientation.z = -0.153;//0.562;
	goal.target_pose.pose.orientation.w = 0.988;//0.827;
	
	std::string aa("goto_turnover_point");
	if (msg->data.c_str() == aa)
	{
		ROS_INFO("Sending goal");
        ac.sendGoal(goal);
        ROS_INFO("Goal has been sended!");
	}
	ac.waitForResult();
}
int main(int argc, char** argv){
  ros::init(argc, argv, "turnover_point");
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
