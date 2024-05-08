/*****************************************************************************
* | File        :   MotorDriver.c
* | Author      :   Waveshare team
* | Function    :   Drive TB6612FNG
* | Info        :
*                TB6612FNG is a driver IC for DC motor with output transistor in
*                LD MOS structure with low ON-resistor. Two input signals, IN1
*                and IN2, can choose one of four modes such as CW, CCW, short
*                brake, and stop mode.
*----------------
* |	This version:   V1.0
* | Date        :   2018-09-04
* | Info        :   Basic version
*
******************************************************************************/
#include "MotorDriver.h"
#include "Debug.h"

/**
 * Code uses two motor hat drivers
 * 
 * 0x40 is the address of the Left Motors
 * 
 * 0x44 is the address of the Right Motors
 * 
 * Call DEV_HARDWARE_I2C_setSlaveAddress() every time you want to change sides
 * Additionally, call PCA9685_SetPWMFreq() every time you change sides
*/

/**
 * Motor rotation.
 *
 * Example:
 * Motor_Init();
 */
void Motor_Init(int motor)
{
    PCA9685_Init(motor);
    PCA9685_SetPWMFreq(100);
}

/**
 * Motor rotation.
 *
 * @param motor: Motor A and Motor B.
 * @param dir: forward and backward.
 * @param speed: Rotation speed.  //(0~100)
 *
 * Example:
 * @code
 * Motor_Run(FORWARD, 50);
 * Motor_Run(BACKWARD, 100);
 */
void Motor_Run(DIR dir, UWORD speed)
{
    if(speed > 100)
        speed = 100;

    switch (dir){
    case FORWARD:
        DEBUG("Moving Forward = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
    break;

    case BACKWARD:
        DEBUG("Moving Backward = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
    break;
    
    case LEFT:
        DEBUG("Strafing Left = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
    break;

    case RIGHT:
        DEBUG("Strafing Right = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
    break;

    case FRONT_LEFT_DIAG:
        DEBUG("Moving Forward Left at a diagonal = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 0);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
    break;

    case FRONT_RIGHT_DIAG:
        DEBUG("Moving Forward Right at a diagonal = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 0);
    break;

    case BACK_LEFT_DIAG:
        DEBUG("Moving Backward Left at a diagonal = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 0);
    break;

    case BACK_RIGHT_DIAG:
        DEBUG("Moving Backward Right at a diagonal = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 0);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
    break;

    case CIRCLE_LEFT:
        DEBUG("Turning Left in place = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
    break;

    case CIRCLE_RIGHT:
        DEBUG("Turning Right in place = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        Motor_Init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
    break;

    default:
    break;

    }
}

/**
 * Motor stop rotation.
 *
 * @param motor: Motor A and Motor B.
 *
 * Example:
 * @code
 * Motor_Stop(MOTORA);
 */
void Motor_Stop(UBYTE motor)
{
    if(motor == MOTOR_FL) {
        PCA9685_SetPwmDutyCycle(PWMA, 0);
    } else {
        PCA9685_SetPwmDutyCycle(PWMB, 0);
    }
}
