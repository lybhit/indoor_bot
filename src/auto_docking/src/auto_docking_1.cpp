#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

ros::Publisher pub_;
int s, nbytes;
struct can_frame frame;

void callback(const std_msgs::String::ConstPtr& msg)
  {
    //.... do something with the input and generate the output...
        ROS_INFO("hello world");
        ROS_INFO("I heard: [%s]", msg->data.c_str());
 	geometry_msgs::Twist vel;
	vel.linear.x = - 0.05;
	ros::Time t_0, t_1;
	t_0 = ros::Time::now();
	t_1 = ros::Time::now();
        std::string aa("autocharge");
	if(msg->data.c_str() == aa)
	{
                ROS_INFO("Receive autocharge message");
		while((t_1 - t_0).toSec() < 4){
                        ROS_INFO("Going to charge!");
			pub_.publish(vel);
			t_1 = ros::Time::now();
		}
                vel.linear.x = 0;
               
		pub_.publish(vel);

                frame.data[0] = 0;
                frame.data[1] = 0;
                frame.data[2] = 0;
                frame.data[3] = 0;
                frame.data[4] = 0;
                frame.data[5] = 0;
                frame.data[6] = 0;
                frame.data[7] = 0;
                for(int i = 0; i<1000; ++i){
                nbytes = write(s, &frame, sizeof(frame));
                ROS_INFO("pub 0 to chasis");
//                close(s);
                }
                return;
	}
    return;
}
    



int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
 ros::NodeHandle n_; 
 ros::Subscriber sub_ = n_.subscribe("/auto_charge", 1, callback);
 pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

 struct sockaddr_can addr;
  struct ifreq ifr;
  s = socket(PF_CAN, SOCK_RAW, CAN_RAW);//创建套接字
  strcpy(ifr.ifr_name, "can0");
  ioctl(s, SIOCGIFINDEX, &ifr);//指定 can0 设备
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;
  bind(s, (struct sockaddr *)&addr, sizeof(addr));//将套接字与can0绑定

  frame.can_id = 0x82;
  frame.can_dlc = 8;

  ros::spin();

  return 0;
}

