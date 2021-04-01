#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "filters/filter_chain.h"
#include <ros/console.h>

class robot_body_filter
{
  filters::FilterChain<sensor_msgs::PointCloud2> filter_chain_;
public:
  robot_body_filter() : filter_chain_("sensor_msgs::PointCloud2")
  {
    filter_chain_.configure("cloud_filter_chain");
    pub_ = n_.advertise<sensor_msgs::PointCloud2>("/camera/depth/color/points_filtered", 1);
    sub_ = n_.subscribe("/camera/depth/color/points", 1, &robot_body_filter::callback, this);
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
  ros::spin();
  return 0;
}
