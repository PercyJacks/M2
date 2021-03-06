/* Lift Controller */
#include "FreeRTOS.h"
#include "task.h"
#include "lift.h"
#include "util.h"

void Init( void ){//Set DDR-registers and initial state of the LEDs
	DDRB = 0xff; // Set port B direction to outputs.  Start with all output off.
	PORTB = 0x00;
    DDRA = 0xff; //Lift Control
    DDRC = 0x00; //Lift Sense
}

void LiftMaster(void *pvPs) { //This is the lift task, it calls lift() which never returns
    lift();
}

int main(void)
{
	Init();
	//create lift task
    xTaskCreate( LiftMaster, // Task Function
                        "Lift Flasher",  // Task Name (useful when simulating)
                        configMINIMAL_STACK_SIZE, // Size of task stack
                        ( void * )  NULL, // Parameter to pass to task at start up, not used here
                        (unsigned portBASE_TYPE) tskIDLE_PRIORITY+1, // Task priority
                        ( xTaskHandle * ) NULL ); // Pointer to reference task with, not used here.

    // Start OS and scheduler
	vTaskStartScheduler(); //Should never return
	return 0;
}

