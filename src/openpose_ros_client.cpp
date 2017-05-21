#include <ros/ros.h>
#include <ros/service_server.h>
#include <cv_bridge/cv_bridge.h>
#include <image_recognition_msgs/GetPersons.h>

#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>


int main(int argc, char **argv){
  ros::init(argc, argv, "openpose_client");
  ros::NodeHandle n;
  ros::ServiceClient srv_client = n.serviceClient<image_recognition_msgs::GetPersons>("detect_poses");

    // Create the classificationrequest and call the service
    image_recognition_msgs::GetPersons person_msg;

    cv::Mat image = cv::imread( "/home/iqit/openpose/examples/media/COCO_val2014_000000000192.jpg", CV_LOAD_IMAGE_COLOR );
    if (image.empty()) return;

    sensor_msgs::ImagePtr im_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
    person_msg.request.image=*im_msg;

   if (!srv_client.call(person_msg))  {
      ROS_ERROR("Service call failed");
      return 1;
   }

   if (person_msg.response.detections.size() > 0){
     ROS_INFO("Detected %d persons", (int) person_msg.response.detections.size());
   }

    return 0;
}
