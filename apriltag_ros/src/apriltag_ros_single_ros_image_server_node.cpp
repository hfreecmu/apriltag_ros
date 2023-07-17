#include "apriltag_ros/common_functions.h"
#include "apriltag_ros/single_ros_image_detector.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "apriltag_ros_single_ros_image_server");

  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");

  apriltag_ros::SingleRosImageDetector continuous_tag_detector(nh, pnh);
  
  ros::spin();
}
