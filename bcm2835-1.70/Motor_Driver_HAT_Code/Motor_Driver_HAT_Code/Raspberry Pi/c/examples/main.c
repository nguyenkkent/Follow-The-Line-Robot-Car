
#include "main.h"

#define LEFT_LINE_SENSOR 21
#define RIGHT_LINE_SENSOR 16
#define IR_SENSOR 20

    
void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:Motor Stop\r\n");
    Motor_Stop(MOTOR_FL);
    Motor_Stop(MOTOR_FR);
    Motor_Stop(MOTOR_BL);
    Motor_Stop(MOTOR_BR);
    DEV_ModuleExit();

    exit(0);
}


void goStraight(){
    printf("Going forward at 100 speed\n");
    //Motor_Run(FORWARD, 100);
}


/**
 * Possible direction combos for Motor_Run:
 *   FORWARD
 *   BACKWARD
 *   LEFT
 *   RIGHT
 *   FRONT_RIGHT_DIAG
 *   FRONT_LEFT_DIAG
 *   BACK_RIGHT_DIAG
 *   BACK_LEFT_DIAG
 *   CIRCLE_RIGHT
 *   CIRCLE_LEFT
*/
int main(void)
{
    //1.System Initialization
    if(DEV_ModuleInit())
        exit(0);

	Motor_Run(FORWARD, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(BACKWARD, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(LEFT, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(RIGHT, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(FRONT_RIGHT_DIAG, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(FRONT_LEFT_DIAG, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(BACK_RIGHT_DIAG, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(BACK_LEFT_DIAG, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(CIRCLE_RIGHT, 100, 100, 100, 100);
    sleep(5);
    Motor_Run(CIRCLE_LEFT, 100, 100, 100, 100);
    sleep(5);
    
    //setup GPIO
	// if (gpioInitialise() == PI_INIT_FAILED){
	// 	printf("Failed to initialize\n");
	// 	return 0;
	// }
    // gpioSetMode(LEFT_LINE_SENSOR, PI_INPUT);
    // gpioSetMode(RIGHT_LINE_SENSOR, PI_INPUT);
    // gpioSetMode(IR_SENSOR, PI_INPUT);

    //start motor
    void goStraight();


    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    while(1) {
    }

    //3.System Exit
    DEV_ModuleExit();
    return 0;
}



