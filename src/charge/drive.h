#ifndef DRIVE_H
#define DRIVE_H

void driveMotor(int motorNum, int direction);

void forward();
void reverse();
void stop();
void left();
void right();
void rightDegrees(int degrees);
void leftDegrees(int degrees);
void search(int front_dist, int back_dist);
void stopMotor(int motor);
void driveForSeconds(int direction, int seconds);
void driveMotor(int motorNum, int direction);

#endif
