/**
 * @file objectDetection2.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream - Using LBP here
 */
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#include <wiringPi.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
String outlet_cascade_name = "20-20-px-375-pos-3170-neg-3-19-16-cascade.xml";
CascadeClassifier outlet_cascade;
String window_name = "OUTLET DETECTION!!!";
/**
 * @function main
 */
int main( void )
{
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascade
    if(!outlet_cascade.load(outlet_cascade_name) ){ printf("(!)Error loading face cascade\n"); return -1; };

    //-- 2. Read video stream
    capture.open(-1);
    if (!capture.isOpened()) {printf("(!)Error opening video capture\n"); return -1; }

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay(frame);

        //-- bail out if escape was pressed
        int c = waitKey(10);
        if( (char)c == 27 ) { break; }
    }
    return 0;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> outlets;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //  Detect outlets
    outlet_cascade.detectMultiScale(frame_gray, outlets, 1.2, 4, 0, Size(20, 20));

    if (wiringPiSetup () == -1) {
      printf("Trouble setting up wiringPi\n");
      exit (1);
    }

    pinMode (25, OUTPUT);  // set led pin to output (wiringPi)
    if (!outlets.size()) {
	digitalWrite(25,LOW);
	printf("Turning off LED, no outlets detected\n");
    }
	 
    for( size_t i = 0; i < outlets.size(); i++ ) {
        pinMode (25, OUTPUT);
	digitalWrite(25, HIGH);
        Mat faceROI = frame_gray( outlets[i] );
        Point center( outlets[i].x + outlets[i].width/2, outlets[i].y + outlets[i].height/2 );
        ellipse( frame, center, Size( outlets[i].width/2, outlets[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
    }

    imshow(window_name, frame);
}
