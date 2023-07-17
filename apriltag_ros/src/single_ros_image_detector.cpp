#include "apriltag_ros/single_ros_image_detector.h"

#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/Header.h>

namespace apriltag_ros
{

SingleRosImageDetector::SingleRosImageDetector (ros::NodeHandle& nh,
                                          ros::NodeHandle& pnh) :
    tag_detector_(pnh)
{
  // Advertise the single image analysis service
  single_image_analysis_service_ =
      nh.advertiseService("single_ros_image_tag_detection",
                          &SingleRosImageDetector::analyzeImage, this);

  ROS_INFO_STREAM("Ready to do tag detection on single images");
}

bool SingleRosImageDetector::analyzeImage(
    apriltag_ros::AnalyzeSingleRosImage::Request& request,
    apriltag_ros::AnalyzeSingleRosImage::Response& response)
{

  ROS_INFO("[ Summoned to analyze image ]");

  // Read the image
  cv::Mat image = cv_bridge::toCvCopy(request.image,"rgb8")->image;

  if (image.data == NULL)
  {
    // Cannot read image
    ROS_ERROR_STREAM("Could not read image");
    return false;
  }

  // Detect tags in the image
  cv_bridge::CvImagePtr loaded_image(new cv_bridge::CvImage(std_msgs::Header(),
                                                            "bgr8", image));
  loaded_image->header.frame_id = request.image.header.frame_id;
  response.tag_detections =
      tag_detector_.detectTags(loaded_image,sensor_msgs::CameraInfoConstPtr(
          new sensor_msgs::CameraInfo(request.camera_info)));


  ROS_INFO("Done!\n");

  return true;
}

} // namespace apriltag_ros
