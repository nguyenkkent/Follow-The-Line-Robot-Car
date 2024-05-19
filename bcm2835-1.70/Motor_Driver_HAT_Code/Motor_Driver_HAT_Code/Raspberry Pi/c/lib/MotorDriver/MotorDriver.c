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
 * hat_init();
 */
void hat_init(int motor)
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
void Motor_Run(DIR dir, UWORD FL_speed, UWORD BL_speed, UWORD FR_speed, UWORD BR_speed)
{
    if(FL_speed > 100){
        FL_speed = 100;
    }
    if(BL_speed > 100){
        BL_speed = 100;
    }
    if(FR_speed > 100){
        FR_speed = 100;
    }
    if(BR_speed > 100){
        BR_speed = 100;
    }

    switch (dir){
    case FORWARD:
        //DEBUG("Moving Forward...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        //DEV_ModuleExit();
        
        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        //DEV_ModuleExit();
        break;

    case BACKWARD:
        //DEBUG("Moving Backward...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        DEV_ModuleExit();
        
        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);        
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        DEV_ModuleExit();
        break;
    
    case LEFT:
        //DEBUG("Moving Left...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);        
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        DEV_ModuleExit();

        hat_init(RIGHT_MOTORS);        
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);        
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();
        break;

    case RIGHT:
        //DEBUG("Moving Right...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();

        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        DEV_ModuleExit();
        break;

    case FRONT_LEFT_DIAG:
        //DEBUG("Moving Foward Left Diagonal...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();

        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 0);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();
        break;

    case FRONT_RIGHT_DIAG:
        //DEBUG("Moving Forward Right Diagonal...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 0);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();

        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();
        break;

    case BACK_LEFT_DIAG:
        //DEBUG("Moving Back Left Diagonal...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //DEV_ModuleExit();
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        DEV_ModuleExit();

        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();
        break;

    case BACK_RIGHT_DIAG:
        //DEBUG("Moving Backward Right Diagonal...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();

        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 0);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        DEV_ModuleExit();
        break;

    case CIRCLE_LEFT:
        //DEBUG("Moving Forward...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        DEV_ModuleExit();

        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        //DEV_ModuleExit();

        break;

    case CIRCLE_RIGHT:
        //DEBUG("Moving Forward...\n");
        hat_init(LEFT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FL_speed);
        //Front Left Motor
        PCA9685_SetLevel(AIN1, 0);
        PCA9685_SetLevel(AIN2, 1);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BL_speed);
        //Back Left Motor
        PCA9685_SetLevel(BIN1, 1);
        PCA9685_SetLevel(BIN2, 0);
        DEV_ModuleExit();

        hat_init(RIGHT_MOTORS);
        PCA9685_SetPwmDutyCycle(PWMA, FR_speed);
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        //DEV_ModuleExit();
        PCA9685_SetPwmDutyCycle(PWMB, BR_speed);
        //Back Right Motor
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
        DEV_ModuleExit();
        
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
void Motor_Stop()
{
    //halting right motors
    hat_init(RIGHT_MOTORS);
    PCA9685_SetPwmDutyCycle(PWMA, 0);
    PCA9685_SetPwmDutyCycle(PWMB, 0);
    DEV_ModuleExit();
    //halting left motors
    hat_init(LEFT_MOTORS);
    PCA9685_SetPwmDutyCycle(PWMA, 0);
    PCA9685_SetPwmDutyCycle(PWMB, 0);
    DEV_ModuleExit();
}