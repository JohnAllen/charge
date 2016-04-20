#include <ros/ros.h>
#include <ros/package.h>
#include <ros/console.h>
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Bool.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"

#include <opencv2/objdetect.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <image_transport/image_transport.h>
#include <iostream>

using namespace std;
using namespace cv;

/* Globals */
String outlet_cascade_path = "20-20-px-375-pos-3170-neg-3-19-16-cascade.xml";
CascadeClassifier outlet_cascade;

int detectOutlets(Mat frame)
{
    std::vector<Rect> outlets;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //  Detect outlets
    outlet_cascade.detectMultiScale(frame_gray, outlets, 1.1, 3, 0, Size(20, 20));

    //if (outlets.size() > 0)
    //{
    cout << outlets.size() << " outlets detected\n";
    return outlets.size();
    //}

    for(size_t i = 0; i < outlets.size(); i++)
    {
        Mat outletROI = frame_gray(outlets[i]);
        //Point center([i].x + outlets[i].width/2, outlets[i].y +outlets[i].height/2);
        //ellipse(frame, center, Size(outlets[i].width/2, outlets[i].height/2 ), 0, 0, 360, Scalar( 255,0,0),2,8,0);
    }
}


int main (int argc, char **argv)
{
    ros::init(argc, argv, "outlet_node");
    ros::NodeHandle outlet_node;
    
    printf("inited outlet_node\n");
    std_msgs::Int8 OUTLET_MSG;
    ros::Publisher outlet_pub = outlet_node.advertise<std_msgs::Int8>("outlet", 100);

    VideoCapture capture;
    Mat frame;

    outlet_cascade_path = ros::package::getPath("charge") + "/" + outlet_cascade_path;
    cout << "charge's package path is " << outlet_cascade_path << "\n";
    if (!outlet_cascade.load(outlet_cascade_path))
    {
        printf("--(!) Couldn't load the outlet cascade file\n"); return -1; 
    }

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
        }
        
        if (detectOutlets(frame))
        {
            OUTLET_MSG.data = 1;
        }
        else
        {
            OUTLET_MSG.data = 0;
            printf("No outlets detected at this time\n");
        }
        outlet_pub.publish(OUTLET_MSG);
        ros::spinOnce();
        r.sleep();              
    }

    return 0;
}
