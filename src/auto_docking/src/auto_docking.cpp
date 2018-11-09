#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h"

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    //Topic you want to subscribe
    sub_ = n_.subscribe("/auto_charge", 1, &SubscribeAndPublish::callback, this);
  }

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
		while((t_1 -t_0).toSec() < 5){
                        ROS_INFO("Going to charge!");
			pub_.publish(vel);
			t_1 = ros::Time::now();
		}
                
                vel.linear.x = 0;
                for(int i=0;i<10000;++i)
                  {
		     pub_.publish(vel);
                  }
                return;
	}
     return;
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
