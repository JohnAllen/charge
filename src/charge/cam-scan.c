
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pca9685.h>

#include "../robot_constants.h"


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
float map(float input, float min, float max) {
  return (input * max) + (1 - input) * min;
}


float range_increment(float min, float max, float millis) { 
  return (max - min) /  millis;
}

int main(void) {
        printf("Scanning back and forth...\n");
        // Setup with pinbase 300 and i2c location 0x40
        int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0) {
          printf("Error in setup\n");
          return fd;
        }

        // Reset board output
        pca9685PWMReset(fd);

	int tick;
	float servo_range = ROT_0_UP_MAX - ROT_0_UP_MIN;

	int camera_scan_time = 10000;
	float increment = range_increment(ROT_0_UP_MIN, ROT_0_UP_MAX, camera_scan_time);
	tick = calcTicks(ROT_0_UP_MIN, HERTZ);
        pwmWrite(SERVO_0, tick);  // set servo to minimum

	printf("At minimum, (%d) beginning to pan.  Waiting for 1.5 seconds.\n", ROT_0_UP_MIN);
	delay(1500);

	float i,j;

	while (1==1) {
	  for (i = ROT_0_UP_MIN; i < ROT_0_UP_MAX;  i+=increment){
	    printf("Panning up. position is %d\n", i);
	    tick = calcTicks(i, HERTZ);
            pwmWrite(SERVO_0, tick);
          }

          for (j = i; j > ROT_0_UP_MIN; j-= increment) {
            printf("Panning backwards. Position: %d/n", j);
            tick = calcTicks(j, HERTZ);
            pwmWrite(SERVO_0, tick);
          }
	}
        return 0;
}


