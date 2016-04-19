#include <stdio.h>
#include "drive.h"
#include <unistd.h>
#include "robot_constants.h"
 
void forward()
{
 driveMotor(1, 1);
 driveMotor(2, 1);
 driveMotor(3, 1);
 driveMotor(4, 1);
}

void reverse()
{
 driveMotor(1, -1);
 driveMotor(2, -1);
 driveMotor(3, -1);
 driveMotor(4, -1);
}

void stop() 
{
 driveMotor(1, 0);
 driveMotor(2, 0);
 driveMotor(3, 0);
 driveMotor(4, 0);
}

void left() 
{
 driveMotor(1, 1);
 driveMotor(2, 1);
 driveMotor(3, -1);
 driveMotor(4, -1);
}

void right()
{
 driveMotor(1, -1);
 driveMotor(2, -1);
 driveMotor(3, 1);
 driveMotor(4, 1);
}

void leftDegrees(int degrees)
{
    
    int i = degrees / 8; // TODO how many degrees per second with ~voltage?
    while (i > 0)
    {
        left();
        sleep(1);
    }          
}

void rightDegrees(int degrees)
{
    
    int i = degrees / 8; // TODO how many degrees per second with ~voltage?
    while (i > 0)
    {
        right();
        sleep(1);
    }          
}

void search(int front_dist, int back_dist) 
{
    int degrees;
    while (1)
    {
        if (front_dist > MIN_FRT_DIST)
        {
            degrees = 90;
            leftDegrees(degrees);
            forward();
        }
        else if (back_dist > MIN_BCK_DIST)
        {
            degrees = 20;
            leftDegrees(degrees);
            reverse();
        }
        else if (front_dist < MIN_FRT_DIST && back_dist < MIN_BCK_DIST)
        {
            // turn 90
            leftDegrees(90);
        }
    }
}


void stopMotor(int motor) 
{

  printf("Stoping motor %d\n", motor);
  switch (motor) {
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      break;
    case 2:
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, LOW);
      break;
    case 4:
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, LOW);
      break;
  }
}

int driveForSeconds(int direction, int seconds) 
{
  
    int i;
    for (i = seconds; i >= 0; i--) {
        
        sleep(1);
    }
    
    
    return 0;
}

/*void driveMotor(int motorNum, int direction)
{

  if (wiringPiSetup () == -1) {
     printf("Trouble setting up wiringPi\n");
     exit (1);
  }
  printf("wiringPi setup, will turn on motors as you specified\n");

  switch (motorNum) {
    case 1:
      switch (direction) {
        case 1:
          forward(IN1, IN2);
	  break;
        case -1:
          reverse(IN1, IN2);
	  break;
        case 0:
          stop(IN1, IN2);
	  break;
      }
  case 2:
    switch (direction) {
      case 1:
        forward(IN3, IN4);
        break;
      case -1:
        reverse(IN3, IN4);
        break;
    }
  case 3:
    switch (direction) {
      case 1:
        forward(IN5, IN6);
        break;
      case -1:
        reverse(IN5, IN6);
        break;

    }
  case 4:
    switch (direction) {
      case 1:
        forward(IN7, IN8);
        break;
      case -1:
        reverse(IN7, IN8);
        break;

    }
}*/
