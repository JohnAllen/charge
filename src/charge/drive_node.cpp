#include "ros/ros.h"
#include <ros/console.h>
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include "drive.h"
#include <pca9685.h>
#include <wiringPi.h>

const int IN1 = 0;  // gpio/bcm 17
const int IN2 = 26; // gpio/bcm 18
const int IN3 = 2;  // gpio/bcm 27
const int IN4 = 3;  // gpio/bcm 22
const int IN5 = 4;  // gpio/bcm 24
const int IN6 = 5;  // gpio/bcm 24
const int IN7 = 6;  // gpio/bcm 25
const int IN8 = 21; // gpio/bcm 5

const int MAX_OUTLET_DIST = 60;
using namespace std;

/*
*   Need three modes: search; outlet-plug-in and position-for-outlet
*   SEARCH: basically keep moving until we find an outlet
*   PLUG_IN: if outlet is close enough to plug in and we are oriented correctly, stop so the damn thing can plug itself in
*   ORIENT_OUTLET: if an outlet is detected but not close enough and we need to travel, rotate or some combination thereof
*   
*   Need all vars available in main function scope:
*/
void distCallback(std_msgs::Int8 dist_msg)
{
    ROS_INFO("I heard: [%d]", dist_msg.data);
}

void outletCallback(const std_msgs::Int8 outlet_msg)
{
    ROS_INFO("I heard: [%s]", outlet_msg);
}

void panangleCallback(const std_msgs::Int8 pan_angle_msg)
{
    ROS_INFO("I heard: [%s]", pan_angle_msg);
}

int main (int argc, char **argv) 
{
    if (wiringPiSetup () == -1)
    {
        printf("Trouble setting up wiringPi\n");
        exit (1);
    } 
    else
    {
        printf("wiringPi setup.  Motors ready\n");
    }   
    ros::init(argc, argv, "drive_node");
    ros::NodeHandle drive_node;
    ros::Subscriber dist_sub = drive_node.subscribe("dist", 100,
distCallback); // Distance is automatically the distance to outlet
    ros::Subscriber outlet_sub = drive_node.subscribe("outlets", 100, outletCallback);
    ros::Subscriber panangle_sub = drive_node.subscribe("pan_angle", 100, panangleCallback);
   
    int front_dist = 100; 
    int back_dist = 100;
    while (ros::ok())
    {
        
        ros::spin();
    }
    return 0;

}
