
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

//While the IR sensor has not detected anything..
void run(){
	int turning = 0;
	printf("Running Elliot's function...");
	Motor_Run(FORWARD, 100, 100, 100, 100);
        while (gpioRead(IR_SENSOR)){
          	printf("IR SENSOR VALUE %d/n", gpioRead(IR_SENSOR));
               //..and while the left line sensor has not detected anything..
		while (gpioRead(LEFT_LINE_SENSOR) && gpioRead( RIGHT_LINE_SENSOR)){
	        	printf("both sensors detected\n");
	      		Motor_Run(FORWARD, 100, 100, 100, 100);

			}       
       		while(gpioRead(LEFT_LINE_SENSOR)){
            		printf("left sensor value %d\n", gpioRead(LEFT_LINE_SENSOR));
	  		// if(!turning){
                	Motor_Run(CIRCLE_LEFT, 100, 100, 100, 100);
			//turning = 1;
	    		//}
        		}
        		//..and while the right line sensor has not detected anything..
        	while(gpioRead(RIGHT_LINE_SENSOR)){

            		printf("right sensor value %d\n", gpioRead(RIGHT_LINE_SENSOR));
			//  if(!turning){
                	Motor_Run(CIRCLE_RIGHT, 100, 100, 100, 100);
 	    		//turning = 1;
        		}
        		//..turning for both is set to 1 so it does not keep moving in that direction
        		//turning = 0;

        	printf("go straight again\n");
        	Motor_Run(FORWARD, 100, 100, 100, 100);
   		 }
		printf("It is running rn");
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
    
	if (!gpioRead(IR_SENSOR)){
        	    Motor_Stop();
       	 };
 
   //3.System Exit
    DEV_ModuleExit();
    return 0;
}

