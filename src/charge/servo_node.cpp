#include "ros/ros.h"
#include "std_msgs/Int.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <ros/console.h>

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <pca9685.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

#define MIN_0 0.9
#define MAX_0 2.1
#define MIN_1 0.9
#define MAX_1 2.1
#define MIN_2 0.9
#define MAX_2 2.1
#define MIN_3 0.9
#define MAX_3 2.1

#define SERVO_0 300
#define SERVO_1 301
#define SERVO_2 302
#define SERVO_3 303 

/**
 *  * Calculate the number of ticks the signal should be high for the required amount of time
 *   */
int calcTicks(float impulseMs, int hertz)
{
    float cycleMs = 1000.0f / hertz;
    return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

/**
 *  * input is [0..1]
 *   * output is [min..max]
 *    */
float map(float input, float min, float max)
{
    return (input * max) + (1 - input) * min;
}

float range_increment(float min, float max, float millis)
{
    return (max - min) / millis;
}

int calcPanAngleFromTick(tick) {
    return 
}

void scan(servo, scan_time)
{
    int tick;
    int camera_scan_time = 10000;
    float increment = range_increment(servo min, servomax, camera_scan_time);
    int angle = angleMicroSec(tick);
    return angle;
}


bool outletDetectedCallback(const std_msgs::Bool::ConstPtr& outlet_msg) 
{
    ROS_INFO("Outlet detected msg is: [%s]", outlet_msg);
    return outlet_msg;
}
int main (int argc, char **argv)
{
    // Setup with pinbase 300 and i2c location 0x40
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
        
    // Reset board output
    pca9685PWMReset(fd);

    ros::init(argc, argv, "servo_node");

    ros::NodeHandle servo_node;

    //int pan_angle =
    ros::Publisher servo_pub = servo_node.advertise<std_msgs::Int>("pan_angle", 100);
  
    ros::Subscriber out_det_sub = servo_node.subscribe("outlet_detected", 100,
outlet_detectedCallback); 
    
    // check if outlet is detected
    while (1==1) {
    
           
        if (!OUTLET_DETECTED) {
            scan();        
        } else if (OUTLET_DETECTED && DISTANCE_INSUFFICIENT) {
            // navigate to a position that is pluggable
        } else {
            // plug in
        }
    }
    pan_angle_msg; 
    servo_node.publish(pan_angle_msg);
    
    ros::Rate loop_rate(10);
    ros::spinOnce();
    return 0;
}
