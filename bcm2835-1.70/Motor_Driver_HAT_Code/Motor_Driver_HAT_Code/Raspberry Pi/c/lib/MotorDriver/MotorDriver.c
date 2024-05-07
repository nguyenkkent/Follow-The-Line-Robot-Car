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
 * Motor_Run(MOTORA, FORWARD, 50);
 * Motor_Run(MOTORB, BACKWARD, 100);
 */
void Motor_Run(UBYTE motor, DIR dir, UWORD speed)
{
    if(speed > 100)
        speed = 100;

    switch (motor){
    case MOTOR_FL:
        DEBUG("Front Left Motor Speed = %d\r\n", speed);
        Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        if(dir == FORWARD) {
            DEBUG("forward...\r\n");
            PCA9685_SetLevel(AIN1, 0);
            PCA9685_SetLevel(AIN2, 1);
        } else if(dir == BACKWARD){
            DEBUG("backward...\r\n");
            PCA9685_SetLevel(AIN1, 1);
            PCA9685_SetLevel(AIN2, 0);
	} else if(dir == LEFT){
            DEBUG("Crab Left...\r\n");
            PCA9685_SetLevel(AIN1, 0);
            PCA9685_SetLevel(AIN2, 1);
	} else {
            DEBUG("Crab Right...\r\n");
            PCA9685_SetLevel(AIN1, 1);
            PCA9685_SetLevel(AIN2, 0);
        }
    break;
    case MOTOR_BL:
	DEBUG("Back Left Motor Speed = %d\r\n", speed);
    Motor_Init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMB, speed);
        if(dir == FORWARD) {
            DEBUG("forward...\r\n");
            PCA9685_SetLevel(BIN1, 0);
            PCA9685_SetLevel(BIN2, 1);
        } else if(dir == BACKWARD){
            DEBUG("backward...\r\n");
            PCA9685_SetLevel(BIN1, 1);
            PCA9685_SetLevel(BIN2, 0);
	} else if(dir == LEFT){
            DEBUG("Crab Left...\r\n");
            PCA9685_SetLevel(BIN1, 0);
            PCA9685_SetLevel(BIN2, 1);
	} else {
            DEBUG("Crab Right...\r\n");
            PCA9685_SetLevel(BIN1, 1);
            PCA9685_SetLevel(BIN2, 0);
        }
     break;
    case MOTOR_FR:
        DEBUG("Front Right Motor Speed = %d\r\n", speed);
        Motor_Init(RIGHT_MOTORS);
        //DEV_HARDWARE_I2C_setSlaveAddress(RIGHT_MOTORS);
        //PCA9685_SetPWMFreq(100);
        PCA9685_SetPwmDutyCycle(PWMA, speed);
        if(dir == FORWARD) {
            DEBUG("forward...\r\n");
            PCA9685_SetLevel(AIN1, 0);
            PCA9685_SetLevel(AIN2, 1);
        } else if(dir == BACKWARD){
            DEBUG("backward...\r\n");
            PCA9685_SetLevel(AIN1, 1);
            PCA9685_SetLevel(AIN2, 0);
	    } else if(dir == LEFT){
            DEBUG("Crab Left...\r\n");
            PCA9685_SetLevel(AIN1, 0);
            PCA9685_SetLevel(AIN2, 1);
	    } else {
            DEBUG("Crab Right...\r\n");
            PCA9685_SetLevel(AIN1, 1);
            PCA9685_SetLevel(AIN2, 0);
        }
     break;
     case MOTOR_BR:
        DEBUG("Back Right Motor Speed = %d\r\n", speed);
        Motor_Init(RIGHT_MOTORS);
        //DEV_HARDWARE_I2C_setSlaveAddress(RIGHT_MOTORS);
        //PCA9685_SetPWMFreq(100);
        PCA9685_SetPwmDutyCycle(PWMB, speed);
        if(dir == FORWARD) {
            DEBUG("forward...\r\n");
            PCA9685_SetLevel(BIN1, 0);
            PCA9685_SetLevel(BIN2, 1);
        } else if(dir == BACKWARD){
            DEBUG("backward...\r\n");
            PCA9685_SetLevel(BIN1, 1);
            PCA9685_SetLevel(BIN2, 0);
	    } else if(dir == LEFT){
            DEBUG("Crab Left...\r\n");
            PCA9685_SetLevel(BIN1, 0);
            PCA9685_SetLevel(BIN2, 1);
	    } else {
            DEBUG("Crab Right...\r\n");
            PCA9685_SetLevel(BIN1, 1);
            PCA9685_SetLevel(BIN2, 0);
        }
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
