#include "ros/ros.h"
#include <ros/console.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "std_msgs/Int8.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <wiringPi.h>
#include <pca9685.h>
#include <iostream>

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

const float PAN_RANGE = MAX_0 - MIN_0;
#define SCAN_TIME 5000

#define SERVO_0 300
#define SERVO_1 301
#define SERVO_2 302
#define SERVO_3 303 

using namespace std;

std_msgs::Int8 OUTLET_DETECTED;

/**
 *  * Calculate the number of ticks the signal should be high for the required amount of time
 *   */
int calcTicks(float impulseMs, int hertz)
{
    float cycleMs = 1000.0f / hertz;
    return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

float map(float input, float min, float max)
{
    return (input * max) + (1 - input) * min;
}

float range_increment(float min, float max, float millis)
{
    return (max - min) / millis;
}

void servoAngle(int servo_num, int angle)
{
    sleep(1);
    float angleRange = 180;
    float servoRange = MAX - MIN;
    float anglePercent = angle / angleRange;
    float servoAngle = MIN + (anglePercent * servoRange);
    int tick = calcTicks(servoAngle, HERTZ);
    pwmWrite(servo_num, tick);
    sleep(1);
}

void scan(int ms)
{
    float increment = range_increment(MIN_0, MIN_1, ms);)
    for (i = MIN_0; i <= MAX_0;  i+=increment)
            {
               cout << "SCANNING FORWARD: %d/n";
                tick = calcTicks(i, HERTZ);
                pwmWrite(SERVO_0, tick);
                int angle = angleFromPWMPulse(tick);
                PAN_ANGLE.data = angle;
            }
            
            for (j = i; j >= MIN_0; j-= increment)
            {
                cout << "SCANNING: %d/n";
                tick = calcTicks(j, HERTZ);
                pwmWrite(SERVO_0, tick);
                int angle = angleFromPWMPulse(tick);
                PAN_ANGLE.data = angle;
            }
}

int angleFromPWMPulse(float pulse)
{
    // example pulse: 1.5 or 1500?
    return angle;   
}

void outletDetectedCallback(std_msgs::Int8 outlet_msg) 
{
    cout << "Outlet detected msg is: " << outlet_msg.data << "\n";
    OUTLET_DETECTED.data = outlet_msg.data;
}

int main (int argc, char **argv)
{
    // Setup with pinbase 300 and i2c location 0x40
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0) {
        printf("Error in setup\n");
        return fd;
    }
        
    pca9685PWMReset(fd);

    ros::init(argc, argv, "arm_node");
    ros::NodeHandle arm_node;
    ros::Publisher arm_pub = arm_node.advertise<std_msgs::Int8>("pan_angle", 100);
    
    ros::Subscriber out_det_sub = arm_node.subscribe("outlet", 100,
 outletDetectedCallback); 

    ros::Rate r(4);
   
    int tick, i, j = 0;
 
    while (ros::ok())
    {
        std_msgs::Int8 PAN_ANGLE; 
       
        servoAngle(SERVO_0, 80);
        if (OUTLET_DETECTED.data > 0)
        {
            cout << "OUTLET DETECTED\n";
            pause();
        }
        else
        {
            cout << "NO OUTLET DETECTED\n";
            scan();
        }
        
        servoAngle(SERVO_0, 100);
        arm_pub.publish(PAN_ANGLE);
        ros::spinOnce();
        r.sleep();
    }
    
    return 0;
}
