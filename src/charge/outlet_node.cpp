#include <ros/ros.h>
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <ros/console.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

void detectOutlets(Mat frame);

/** Global variables */
String outlet_cascade_path = "20-20-px-375-pos-3170-neg-3-19-16-cascade.xml";
CascadeClassifier outlet_cascade;


int main (int argc, char **argv)
{
    ros::init(argc, argv, "outlet_node");
    ros::NodeHandle outlet_node;

    std_msgs::Bool OUTLET_DETECTED;
    ros::Publisher outlet_pub = outlet_node.advertise<std_msgs::Bool>("outlet", 100);

    VideoCapture capture;
    Mat frame;

    if(!outlet_cascade.load(outlet_cascade_name) ){ printf("--(!)ERROR loading cascade\n"); return -1; };

    capture.open(-1) ;
    if (!capture.isOpened())
    {
        printf("--(!)Error opening video capture\n"); return -1;
    }
    
    ros::Rate r(1);

    while (ros::ok() && capture.read(frame))
    {
        if (frame.empty())
        {
            printf("outlet frame empty PROBLEM\n");
            // TODO ROS DEBUG
        }
        OUTLET_DETECTED = detectOutlets(frame);
        if (OUTLET_DETECTED)
        {
            printf("outlet detected?: %s\n", OUTLET_DETECTED);
            OUTLET_DETECTED.data = true;
            outlet_pub.publish(OUTLET_DETECTED;
            ros::spinOnce();
        }

        r.sleep();              
    }

    return 0;
}

void detectOutlets(Mat frame)
{
    std::vector<Rect> outlets;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //  Detect outlets
    outlet_cascade.detectMultiScale(frame_gray, outlets, 1.1, 2, 0, Size(20, 20));

    //if (outlets.size() > 0)
    //{
    return outlets.size();
    //}
    
    for(size_t i = 0; i < outlets.size(); i++)
    {
        Mat outletROI = frame_gray(outlets[i]);
        Point center([i].x + outlets[i].width/2, outlets[i].y +outlets[i].height/2);
        ellipse(frame, center, Size(outlets[i].width/2, outlets[i].height/2 ), 0, 0, 360, Scalar( 255,0,0),2,8,0);

}

