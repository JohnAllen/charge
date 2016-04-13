#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

#define MIN_FRT_DIST 80 
#define MIN_BCK_DIST 60


/*
 * We don't necessarily want each servo to move its entire possible path.  That would be very bad.
 * So we hardcode limits in this file.  We can also add some constants for special servo positions. 
 * E.g. when the arm is upright scanning for outlets, we will hardcode that pwm position here. 
*/

/*
 * Rotation servo. #0  Pan servo that rotates the arm around the y axis
 */
#define ROT_0_DWN_MIN 1.5
#define ROT_0_DWN_MAX 1.6
#define ROT_1_DWN_MIN 0.9
#define ROT_1_UP_MAX 2.0 
#define ROT_0_FRT 2.1
#define ROT_0_BAK 1.8
#define ROT_0_PRT 2.045
#define ROT_0_SBD 1.55

/*
 * Lift servo: lifts the entire arm.  Also holds it upright while scanning.
 */
#define LIFT_1_MIN  0.9
#define LIFT_1_VERT 1.615
#define LIFT_1_MAX  2.1

/*
 *
 */
#define MIN_2 0.9
#define MAX_2 2.1

/*
 * 
 */

#define END_3_MIN 0.9
#define END_3_MID 1.6
#define END_3_MAX 2.1

/*
 * 
 */
#define SERVO_0 300
#define SERVO_1 301
#define SERVO_2 302
#define SERVO_3 303 

