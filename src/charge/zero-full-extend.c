#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include "pins.h"

#include <pca9685.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50


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
        printf("PCA9685 servo example\n");

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
	  float lowest = 0.9;
          int tick = calcTicks(lowest, HERTZ);
          pwmWrite(PIN_BASE + 1, tick);
          delay(2000);

	  //Set  #1 servo to highest  setting
	  float highest = 2.1;
          tick = calcTicks(highest, HERTZ);
          pwmWrite(PIN_BASE + 1, tick);
          delay(2000);
        }

        return 0;
}


