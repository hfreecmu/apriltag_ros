#ifndef APRILTAG_ROS_SINGLE_ROS_IMAGE_DETECTOR_H
#define APRILTAG_ROS_SINGLE_ROS_IMAGE_DETECTOR_H

#include "apriltag_ros/common_functions.h"
#include <apriltag_ros/AnalyzeSingleRosImage.h>

namespace apriltag_ros
{

class SingleRosImageDetector
{
 private:
  TagDetector tag_detector_;
  ros::ServiceServer single_image_analysis_service_;
  
 public:
  SingleRosImageDetector(ros::NodeHandle& nh, ros::NodeHandle& pnh);

  // The function which provides the single image analysis service
  bool analyzeImage(apriltag_ros::AnalyzeSingleRosImage::Request& request,
                     apriltag_ros::AnalyzeSingleRosImage::Response& response);
};

} // namespace apriltag_ros

#endif // APRILTAG_ROS_SINGLE_IMAGE_DETECTOR_H
