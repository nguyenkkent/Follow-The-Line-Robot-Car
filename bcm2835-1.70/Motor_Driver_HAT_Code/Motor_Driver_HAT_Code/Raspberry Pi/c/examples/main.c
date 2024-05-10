
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

/*
 * Elliot's take on this
*/
void run(){
	int turning = 0;
	printf("Running Elliot's function...");
    while (!gpioRead(IR_SENSOR)){
        while(gpioRead(LEFT_LINE_SENSOR)){
            printf("turning left\n");
	    if(!turning){
                Motor_Run(CIRCLE_LEFT, 100, 100, 100, 100);
		turning = 1;
	    }
        }

        while(gpioRead(RIGHT_LINE_SENSOR)){
            printf("turning right\n");
	    if(!turning){
                Motor_Run(CIRCLE_RIGHT, 100, 100, 100, 100);
 	    	turning = 1;
	    }
        }

        printf("go straight again\n");
        Motor_Run(FORWARD, 100, 100, 100, 100);
    }
}

//End Elliot's section


void goStraight(){
    printf("Going forward at 100 speed\n");
    Motor_Run(FORWARD, 100, 100, 100, 100);
}

void turnLeft(){
    printf("Turning left\n");
    int pwm = 100;
    while(gpioRead(!LEFT_LINE_SENSOR)){
        pwm = pwm - 10;
        Motor_Run(FORWARD, pwm, pwm, 100, 100);
    }
    //assertion: car is centered
    //motor foward 100%
    Motor_Run(FORWARD, 100, 100, 100, 100);
}

void turnRight(){
    printf("Turning right\n");
    int pwm = 100;
    while(gpioRead(!RIGHT_LINE_SENSOR)){
        pwm = pwm - 10;
        Motor_Run(FORWARD, 100, 100, pwm, pwm);
    }
    //assertion: car is centered
    //motor foward 100%
    Motor_Run(FORWARD, 100, 100, 100, 100);
}


void crab(){
    /*
    left front and back right motor set to
    */
}
int main(void)
{
    //1.System Initialization
    if(DEV_ModuleInit())
        exit(0);
    
    //setup GPIO
	if (gpioInitialise() == PI_INIT_FAILED){
		printf("Failed to initialize\n");
		return 0;
	}
    gpioSetMode(LEFT_LINE_SENSOR, PI_INPUT);
    gpioSetMode(RIGHT_LINE_SENSOR, PI_INPUT);
    gpioSetMode(IR_SENSOR, PI_INPUT);
    printf("LEFT_LINE_SENSOR: %d\n", gpioRead(LEFT_LINE_SENSOR));
    printf("RIGHT_LINE_SENSOR: %d\n", gpioRead(RIGHT_LINE_SENSOR));
    printf("IR_SENSOR: %d\n", gpioRead(IR_SENSOR));

    //start motor
    //goStraight();
    //Motor_Run(CIRCLE_LEFT, 100, 100, 100, 100);
    //sleep(5);
    run(); //Elliot's function

    /*
    while (1){
        if (!gpioRead(LEFT_LINE_SENSOR)){
            turnLeft();
        }
        if (!gpioRead(RIGHT_LINE_SENSOR)){
            turnRight();
        }
        if (!gpioRead(IR_SENSOR)){
            Motor_Stop();
        };
    }*/

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    while(1) {
    }
    
    //3.System Exit
    DEV_ModuleExit();
    return 0;
}



