#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <stdio.h>
#include <ros/ros.h>
#include <ros/console.h>
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"

using namespace std;
using namespace cv;

void detectOutlets(Mat frame);

/** Global variables */
String outlet_cascade_path = "20-20-px-375-pos-3170-neg-3-19-16-cascade.xml";
CascadeClassifier outlet_cascade;
String window_name = "Capture - OUTLET DETECTION!!!";
/**
 * @function main
 */
int main(int argc, char **argv)
{
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascade
    if(!outlet_cascade.load(outlet_cascade_name) ){ printf("--(!)ERROR loading cascade\n"); return -1; };

    
    //-- 2. Read the video stream
    capture.open(-1) ;
    if (!capture.isOpened()) {printf("--(!)Error opening video capture\n"); return -1; }

    while (capture.read(frame) )
    {
        if(frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectOutlets(frame);
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

    for(size_t i = 0; i < outlets.size(); i++) {
        Mat outletROI = frame_gray( faces[i] );
        Point center( [i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
}

                           
