
#include "main.h"


#define LEFT_LINE_SENSOR 21
#define RIGHT_LINE_SENSOR 16
#define FRONT_IR_SENSOR 20
#define REAR_IR_SENSOR 12
/*
How to handle when both line sensors are triggered:
1. Keep track of what the last movement call as (move left or right)
2. if both line sensors are triggered then move the car the in the OPPOSITE direction of the most recent
movement. For example if the last call was to turn right, there are three possbilities.
	2a. if the line keeps going right then we're good, no adjustment needed
 	2b. if the line goes go straight and both line sensors are detected, this means that
  	    our car is pointed too far to the right and we need to turn hard left to re-center
    2c. if the goes left, then again the car is pointed too much "right" and we need to turn left to recenter.
*/
    
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

//This function lets the car move forward
void goStraight(){
    //printf("Going forward at 100 speed\n");
    Motor_Run(FORWARD, 100, 100, 100, 100);
}

int crab(){
    //move right until we clear obstacle

    printf("FRONT_IR_SENSOR before the crab function: %d\n", gpioRead(FRONT_IR_SENSOR));
    // for some reason the reading here is 0 while there is an obstacle

    clock_t start_time = clock();
    while (!gpioRead(FRONT_IR_SENSOR)){
        printf("Crabing right, GPIO value: %d\n", gpioRead(FRONT_IR_SENSOR));
        Motor_Run(RIGHT,100,100,100,100);
    }
    clock_t end_time = clock();
    double loop_duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Loop duration: %f seconds\n", loop_duration);

    sleep((unsigned int)loop_duration);

    printf("Cleared front IR sensor\n");

    //move forward until we trigger the side rear IR sensor
    printf("Going straight until rear IR sensor triggers\n");
    while (gpioRead(REAR_IR_SENSOR)){ //1 == no obstacle
        goStraight();
    }
    //make sure the rear of the car clears the obstacle
    sleep(1);
    printf("rear IR sensor triggered\n");

    //move left until we hit the line
    while ( !gpioRead(LEFT_LINE_SENSOR) || !gpioRead(RIGHT_LINE_SENSOR) ){
        Motor_Run(LEFT,100,100,100,100);
    }
    //return execution to the back to main function and run() function
    return 0;
    
}

//While the IR sensor has not detected anything..
void run(){
	printf("Running Elliot's function...\n");
	goStraight();
    int lastDirection = 0; // 1==left, 2==right

        while (gpioRead(FRONT_IR_SENSOR)){
               //..and while the left line sensor has not detected anything..
		    while (gpioRead(LEFT_LINE_SENSOR) && gpioRead( RIGHT_LINE_SENSOR)){
                if (lastDirection==1){
                    while (gpioRead(LEFT_LINE_SENSOR) && gpioRead( RIGHT_LINE_SENSOR)){
                        Motor_Run(CIRCLE_RIGHT,100,100,100,100);
                    }
                    goStraight();

                }
                else{
                   while (gpioRead(LEFT_LINE_SENSOR) && gpioRead( RIGHT_LINE_SENSOR)){
                        Motor_Run(CIRCLE_LEFT,100,100,100,100);
                    }
                    goStraight();
                    
                }
	        	//printf("both sensors detected\n");
	      		goStraight();
			}
       		while(gpioRead(LEFT_LINE_SENSOR)){
            		//printf("left sensor value %d\n", gpioRead(LEFT_LINE_SENSOR));
                	Motor_Run(CIRCLE_LEFT, 100, 100, 100, 100);
                    lastDirection = 1;
        		}
        		//..and while the right line sensor has not detected anything..
        	while(gpioRead(RIGHT_LINE_SENSOR)){
            		//printf("right sensor value %d\n", gpioRead(RIGHT_LINE_SENSOR));
                	Motor_Run(CIRCLE_RIGHT, 100, 100, 100, 100);
                    lastDirection = 2;
        		}
        		//..turning for both is set to 1 so it does not keep moving in that direction

        	//printf("go straight again\n");
        	goStraight();
   		}



        printf("Run function ending, calling MotorStop()\n");
        Motor_Stop();
}

//End of Elliot's section

//ALL of the below is an older version of the above. We left it just in-case




void testMovements(){

    printf("Moving FORWARD\n");
	Motor_Run(FORWARD, 100, 100, 100, 100);
    sleep(5);
    printf("Moving BACKWARDS\n");
    Motor_Run(BACKWARD, 100, 100, 100, 100);
    sleep(5);
    printf("Moving LEFT\n");
    Motor_Run(LEFT, 100, 100, 100, 100);
    sleep(5);
    printf("Moving RIGHT\n");
    Motor_Run(RIGHT, 100, 100, 100, 100);
    sleep(5);
    printf("Moving FRONT_RIGHT_DIAG\n");
    Motor_Run(FRONT_RIGHT_DIAG, 100, 100, 100, 100);
    sleep(5);
    printf("Moving FRONT_LEFT_DIAG\n");
    Motor_Run(FRONT_LEFT_DIAG, 100, 100, 100, 100);
    sleep(5);
    printf("Moving BACK_RIGHT_DIAG\n");
    Motor_Run(BACK_RIGHT_DIAG, 100, 100, 100, 100);
    sleep(5);
    printf("Moving BACK_LEFT_DIAG\n");
    Motor_Run(BACK_LEFT_DIAG, 100, 100, 100, 100);
    sleep(5);
    printf("Moving CIRCLE_RIGHT\n");
    Motor_Run(CIRCLE_RIGHT, 100, 100, 100, 100);
    sleep(5);
    printf("Moving CIRCLE_LEFT\n");
    Motor_Run(CIRCLE_LEFT, 100, 100, 100, 100);
    sleep(5);
}

void testIRSensor(){
    // printf("Before while-loop reading: : %d\n", gpioRead(FRONT_IR_SENSOR));
    // while(gpioRead(FRONT_IR_SENSOR)){
    //     printf("%d\n", gpioRead(FRONT_IR_SENSOR));
    //     sleep(1);
    // }
    // printf("After breaking while-loop reading: %d\n", gpioRead(FRONT_IR_SENSOR));


    printf("Testing REAR IR sensor : %d\n", gpioRead(REAR_IR_SENSOR));
    while(gpioRead(REAR_IR_SENSOR)){
    printf("%d\n", gpioRead(REAR_IR_SENSOR));
    sleep(1);
    }
    printf("REAR IR sensor outside loop : %d\n", gpioRead(REAR_IR_SENSOR));
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
    gpioSetMode(FRONT_IR_SENSOR, PI_INPUT);
    gpioSetMode(REAR_IR_SENSOR, PI_INPUT);

    /*
    line sensor 0 means no black line detected
    IR sensor 1 means no obstacle detected
    */

    //start motor
    while (gpioRead(FRONT_IR_SENSOR)){
        run();
        //assertion: front IR sensor detects obstacle and run() ends
        crab();
        //assertion: there is no longer an obstacle and we hit the line
    }
    

        

    //testMovements();
    //testIRSensor();
    //this handles when when we need to cmd + c to stop the motor
    signal(SIGINT, Handler);
    while(1) {
        
    }
    Motor_Stop();

   //3.System Exit
   // DEV_ModuleExit();
    return 0;
}