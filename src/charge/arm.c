#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <pca9685.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

#define MIN_0 1.2
#define MAX_0 2.1
#define MIN_1 1.0
#define MAX_1 1.95
#define MIN_2 0.9
#define MAX_2 2.1
#define MIN_3 0.9
#define MAX_3 2.1

#define MID 1.5

//#define SERVO_0 PIN_BASE 0
#define SERVO_0 300
#define SERVO_1 301
#define SERVO_2 302
#define SERVO_3 303



/**
 * Calculate the number of ticks the signal should be high for the required amount of time
 */
int calcTicks(float impulseMs, int hertz)
{
        float cycleMs = 1000.0f / hertz;
        return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

/**
 * input is [0..1]
 * output is [min..max]
 */
float map(float input, float min, float max)
{
        return (input * max) + (1 - input) * min;
}


int main(void)
{
        printf("Moving #1 servo to its full range\n");

        // Setup with pinbase 300 and i2c location 0x40
        int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0) {
          printf("Error in setup\n");
          return fd;
        }

        // Reset all output
        pca9685PWMReset(fd);

        while (1 == 1) {
	  //Set  #1 servo to lowest setting
	  printf("Moving servo to lowest point\n");

	  // PAN BASE CIRCULAR
	  int tick;
/*	  tick = calcTicks(MIN_0, HERTZ);
	  pwmWrite(SERVO_0, tick);

	  tick = calcTicks(MIN_1, HERTZ);
          pwmWrite(SERVO_1, tick);
 
	  tick = calcTicks(MIN_2, HERTZ);
	  pwmWrite(SERVO_2, tick);

	  tick = calcTicks(MIN_3, HERTZ);
          pwmWrite(SERVO_3, tick);
          delay(2500);
*/
	  tick = calcTicks(MAX_0, HERTZ);
	  pwmWrite(SERVO_0, tick);

	  tick = calcTicks(MAX_1, HERTZ);
          pwmWrite(SERVO_1, tick);

	  tick = calcTicks(MAX_2, HERTZ);
	  pwmWrite(SERVO_2, tick);

	  tick = calcTicks(MAX_3, HERTZ);
          pwmWrite(SERVO_3, tick);
          delay(2500);
        }

        return 0;
}


