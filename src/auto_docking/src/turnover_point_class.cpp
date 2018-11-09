#include <ros/ros.h>
#include "std_msgs/String.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class TurnoverPoint
{
public:
	TurnoverPoint();

private:
	void callback(const std_msgs::String::ConstPtr& msg);

	ros::NodeHandle nh_, private_nh;
	ros::Subscriber sub_;
	double a_x_, a_y_, a_z_, a_w_, b_x_, b_y_, b_z_, b_w_, c_x_, c_y_, c_z_, c_w_;
};


TurnoverPoint::TurnoverPoint() : private_nh("~")
{
	private_nh.param("a_x", a_x_, 0.0); 
	private_nh.param("a_y", a_y_, 0.0);
	private_nh.param("a_z", a_z_, 0.0);
	private_nh.param("a_w", a_w_, 1.0); 

	private_nh.param("b_x", b_x_, 0.0); 
	private_nh.param("b_y", b_y_, 0.0);
	private_nh.param("b_z", b_z_, 0.0);
	private_nh.param("b_w", b_w_, 1.0);

	private_nh.param("c_x", c_x_, 0.0); 
	private_nh.param("c_y", c_y_, 0.0);
	private_nh.param("c_z", c_z_, 0.0);
	private_nh.param("c_w", c_w_, 1.0);

	sub_ = nh_.subscribe("goto_turnover_point", 10, &TurnoverPoint::callback, this);
}



void TurnoverPoint::callback(const std_msgs::String::ConstPtr& msg)
{
    MoveBaseClient ac("move_base", true);
	
  while(!ac.waitForServer(ros::Duration(1.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
    move_base_msgs::MoveBaseGoal goal_0;

    goal_0.target_pose.header.frame_id = "map";
    goal_0.target_pose.header.stamp = ros::Time::now();
    goal_0.target_pose.pose.position.x = a_x_; //;
    goal_0.target_pose.pose.position.y = a_y_;//;

    ROS_INFO("a_x = %f",a_x_);
    ROS_INFO("a_y = %f",a_y_);
    ROS_INFO("a_z = %f",a_z_);
    ROS_INFO("a_w = %f",a_w_);
    	
    goal_0.target_pose.pose.orientation.x = 0.0;
    goal_0.target_pose.pose.orientation.y = 0.0;
    goal_0.target_pose.pose.orientation.z = a_z_;
    goal_0.target_pose.pose.orientation.w = a_w_;


    move_base_msgs::MoveBaseGoal goal_1;
    goal_1.target_pose.header.frame_id = "map";
    goal_1.target_pose.header.stamp = ros::Time::now();
    goal_1.target_pose.pose.position.x = b_x_; 
    goal_1.target_pose.pose.position.y = b_y_;
  
    goal_1.target_pose.pose.orientation.x = 0.0;
    goal_1.target_pose.pose.orientation.y = 0.0;
    goal_1.target_pose.pose.orientation.z = b_z_;
    goal_1.target_pose.pose.orientation.w = b_w_;

    move_base_msgs::MoveBaseGoal goal_2;
    goal_2.target_pose.header.frame_id = "map";
    goal_2.target_pose.header.stamp = ros::Time::now();
    goal_2.target_pose.pose.position.x = c_x_; 
    goal_2.target_pose.pose.position.y = c_y_;
  
    goal_2.target_pose.pose.orientation.x = 0.0;
    goal_2.target_pose.pose.orientation.y = 0.0;
    goal_2.target_pose.pose.orientation.z = c_z_;
    goal_2.target_pose.pose.orientation.w = c_w_;
  
    std::string aa("goto_turnover_point_0");
    std::string bb("goto_turnover_point_1");
    std::string cc("goto_turnover_point_2");

  if(msg->data.c_str() == aa)
    ac.sendGoal(goal_0);
  else if(msg->data.c_str() == bb)
    ac.sendGoal(goal_1);
  else if(msg->data.c_str() == cc)
    ac.sendGoal(goal_2);
  else
    return;

}



int main(int argc, char** argv){

  ros::init(argc, argv, "turnover_point_class");

  TurnoverPoint turnover_point;

  
  ros::spin();
  
//  return 0;
}
