
#include "main.h"

#define LEFT_LINE_SENSOR 21
#define RIGHT_LINE_SENSOR 16
#define IR_SENSOR 20
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


//While the IR sensor has not detected anything..
void run(){
	int turning = 0;
	printf("Running Elliot's function...");
	Motor_Run(FORWARD, 100, 100, 100, 100);
    printf("IR SENSOR VALUE %d/n", gpioRead(IR_SENSOR));
    int lastDirection = 0; // 1==left, 2==right

        while (gpioRead(IR_SENSOR)){
               //..and while the left line sensor has not detected anything..
		    while (gpioRead(LEFT_LINE_SENSOR) && gpioRead( RIGHT_LINE_SENSOR)){
                if (lastDirection==1){
                    while (gpioRead(LEFT_LINE_SENSOR) && gpioRead( RIGHT_LINE_SENSOR)){
                        Motor_Run(CIRCLE_RIGHT,100,100,100,100);
                    }
                    Motor_Run(FORWARD, 100, 100, 100, 100);

                }
                else{
                   while (gpioRead(LEFT_LINE_SENSOR) && gpioRead( RIGHT_LINE_SENSOR)){
                        Motor_Run(CIRCLE_LEFT,100,100,100,100);
                    }
                    Motor_Run(FORWARD, 100, 100, 100, 100);
                    
                }
	        	//printf("both sensors detected\n");
	      		Motor_Run(FORWARD, 100, 100, 100, 100);
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
        	Motor_Run(FORWARD, 100, 100, 100, 100);
   		}

        printf("IR SENSOR VALUE OUTSIDE OUTER WHILE-LOOP: %d/n", gpioRead(IR_SENSOR));
		// printf("It is running rn");
}

//End of Elliot's section

//ALL of the below is an older version of the above. We left it just in-case

//This function lets the car move forward.. duh
void goStraight(){
    printf("Going forward at 100 speed\n");
    Motor_Run(FORWARD, 100, 100, 100, 100);
}

//This function lets the car move left
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
} //First we gotta turn the wheels left, and then we move the car forward in the left direction

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
} //First we gotta turn the wheels left, and then we move the car forward in the left direction 
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

    /*
    line sensor 0 means no black line detected
    IR sensor 1 means no obstacle detected
    */
    printf("LEFT_LINE_SENSOR: %d\n", gpioRead(LEFT_LINE_SENSOR));
    printf("RIGHT_LINE_SENSOR: %d\n", gpioRead(RIGHT_LINE_SENSOR));
    printf("IR_SENSOR: %d\n", gpioRead(IR_SENSOR));

    //start motor
    run(); 
    //testMovements();


    signal(SIGINT, Handler);
    while(1) {
        
    }
    Motor_Stop();

   //3.System Exit
   // DEV_ModuleExit();
    return 0;
}