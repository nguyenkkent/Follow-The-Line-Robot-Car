
#include "main.h"

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

int main(void)
{
    //1.System Initialization
    if(DEV_ModuleInit())
        exit(0);
    
    //2.Motor Initialization
    Motor_Init();

    printf("Motor_Run\r\n");
    Motor_Run(MOTOR_FL, FORWARD, 100);
    Motor_Run(MOTOR_FR, FORWARD, 100);
    Motor_Run(MOTOR_BL, FORWARD. 100);
    Motor_Run(MOTOR_BR, FORWARD, 100);

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    while(1) {

    }

    //3.System Exit
    DEV_ModuleExit();
    return 0;
}



