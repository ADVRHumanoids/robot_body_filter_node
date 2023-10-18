#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "filters/filter_chain.hpp"
#include <ros/console.h>

class robot_body_filter
{
  filters::FilterChain<sensor_msgs::PointCloud2> filter_chain_;
public:
  robot_body_filter() : filter_chain_("sensor_msgs::PointCloud2")
  {
    ros::NodeHandle n("~");
    filter_chain_.configure(ros::this_node::getName() + "/cloud_filter_chain");
    pub_ = n_.advertise<sensor_msgs::PointCloud2>("/cloud_filtered", 1);
    sub_ = n_.subscribe("/cloud_in", 1, &robot_body_filter::callback, this);
  }
  void callback(const sensor_msgs::PointCloud2ConstPtr& input)
  {
    sensor_msgs::PointCloud2 output;
    filter_chain_.update(*input, output);
    pub_.publish(output);
  }
private:
  ros::NodeHandle n_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "load_filter_chain");
  robot_body_filter rbf;

  ros::NodeHandle n("~");
  ros::Rate rate(n.param("rate", 100.0));
  
  while(ros::ok())
  {
    ros::spinOnce();
    rate.sleep();
  }
  
  return 0;
}
