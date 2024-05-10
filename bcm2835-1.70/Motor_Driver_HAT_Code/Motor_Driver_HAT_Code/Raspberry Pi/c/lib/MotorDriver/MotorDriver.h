/*****************************************************************************
* | File        :   MotorDriver.h
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
#ifndef __TB6612FNG_
#define __TB6612FNG_

#include "DEV_Config.h"
#include "PCA9685.h"

//GPIO config
#define PWMA        PCA_CHANNEL_0
#define AIN1        PCA_CHANNEL_1
#define AIN2        PCA_CHANNEL_2
#define PWMB        PCA_CHANNEL_5
#define BIN1        PCA_CHANNEL_3
#define BIN2        PCA_CHANNEL_4

#define MOTOR_FL       0
#define MOTOR_BL       1
#define MOTOR_FR       2 //not sure if 2 and 3 are the right number for this
#define MOTOR_BR       3

#define RIGHT_MOTORS    0x44
#define LEFT_MOTORS     0x40

typedef enum {
    FORWARD  = 0,
    BACKWARD = 1,
    LEFT = 2,
    RIGHT = 3,
    FRONT_RIGHT_DIAG = 4,
    FRONT_LEFT_DIAG = 5,
    BACK_RIGHT_DIAG = 6,
    BACK_LEFT_DIAG = 7,
    CIRCLE_RIGHT = 8,
    CIRCLE_LEFT = 9,
} DIR;

void hat_init(int motor);
void Motor_Run(DIR dir, UWORD FL_speed, UWORD BL_speed, UWORD FR_speed, UWORD BR_speed);
void Motor_Stop();

#endif
