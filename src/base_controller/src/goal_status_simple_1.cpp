#include "ros/ros.h"  //ros需要的头文件
#include <geometry_msgs/Twist.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include <string>
#include "std_msgs/String.h"
using namespace std;

ros::Publisher status_pub;
// add pre_id;
std::string id, pre_id;

move_base_msgs::MoveBaseActionGoal target_goal, last_goal;
static geometry_msgs::Pose initial_pose;

void callback_amcl(const geometry_msgs::PoseWithCovarianceStamped & amcl_pose)//订阅/cmd_vel主题回调函数
{
	std_msgs::Float64 done_ratio;
//	static geometry_msgs::Pose initial_pose;
       if(id.empty())
       	{
       		initial_pose = amcl_pose.pose.pose;
       		last_goal.goal.target_pose.pose = amcl_pose.pose.pose;
                   done_ratio.data = 1.0;
       		status_pub.publish(done_ratio);
                    pre_id = id;
       		return;
       	}
       else if(id.compare(pre_id) != 0)
            //initial_pose = last_goal.goal.target_pose.pose;
           {
                initial_pose = amcl_pose.pose.pose;
                pre_id = id;
           } 

      geometry_msgs::Pose pose;
      pose.position.x = amcl_pose.pose.pose.position.x;
      pose.position.y = amcl_pose.pose.pose.position.y;

      

	double whole_length = hypot(abs(target_goal.goal.target_pose.pose.position.x - initial_pose.position.x), abs(target_goal.goal.target_pose.pose.position.y - initial_pose.position.y));
	double done_length = hypot(abs(pose.position.x - initial_pose.position.x), abs(pose.position.y - initial_pose.position.y));

       ROS_INFO("target_pose: %f, %f", target_goal.goal.target_pose.pose.position.x, target_goal.goal.target_pose.pose.position.y);
       ROS_INFO("initial_pose: %f, %f", initial_pose.position.x, initial_pose.position.y);
       ROS_INFO("length: %f, %f", whole_length, done_length);

	done_ratio.data = done_length / whole_length;
	if (done_ratio.data >= 1.0 || done_ratio.data >= 0.95)
		{
               done_ratio.data = 1.0;
             }
 //     done_ratio.data = 0;
	status_pub.publish(done_ratio);

//	last_goal = target_goal;
	
}

void callback_goal(const  move_base_msgs::MoveBaseActionGoal& goal_input)
{
	target_goal = goal_input;
	id = target_goal.goal_id.id;
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "cmd_node");//初始化串口节点
    ros::NodeHandle n;  //定义节点进程句柄

    ros::Subscriber pos_sub_map = n.subscribe("/amcl_pose", 10, callback_amcl);
    ros::Subscriber goal_sub = n.subscribe("/move_base/goal", 10, callback_goal);
    status_pub = n.advertise<std_msgs::Float64>("/goal_status", 10);

    ros::AsyncSpinner spinner(2);
    spinner.start();
    ros::waitForShutdown();
    return 0;
}


