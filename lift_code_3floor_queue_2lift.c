#include "FreeRTOS.h"
#include "task.h"
#include "lift.h"
#include "queue.h"


/*

Remember T0 is bottom floor, T2 is top and T1 or TM is the middle which is not used.


This task spends most of its time sleeping, so the infinite loop does not stop other things working.

*/



ISR(INT0_vect){ //Catch interrupt 0 PD2 is the interrupt try to get PD2 high on pin change with logic gates
    signed portCHAR prt;;
	prt = PORTC;
    xQueueSendFromISR( xRxedChars, &prt, pdFALSE); //Post value of PORTC to queue
}




void lift(void){
    unsigned char t, q;
    unsigned char State; // Start going down.
    PORTA = 0xFF;
    State = To0;
	
	//I'm not sure how queues work in RTOS, trying to use these, I think this exists in queue.c, however, if this doesnt work,
	//try implementing a queue using a 
	portENTER_CRITICAL();// Create queue and enable interupts. Dont want anything getting in the way
        {
		xRxedChars = xQueueCreate( 4, ( unsigned portBASE_TYPE ) sizeof( signed portCHAR ) );
        MCUCR = MCUCR | 0x03;
        GICR = GICR | 0x40; // Enable interupt 0
        }
	portEXIT_CRITICAL();
	
	for(;;)
	{
        t = xQueueReceive( xRxedChars, &store, 250 * 5 ); // read lift sensors from queue, 5 second time out
        t = (~t) & 0x7F; // Lift is negative logic
		do //execute at least once
		{
			switch(State) {
				case To0:
					q = MotorOn | MotorDown | Lamp0;
					if(t & Floor0)
						State = At0;
					else
						State = To0;
					break;
				case To1:
					q |= MotorOn | Lamp1;
					if(t & Floor1)
						State = At1;
					else
						State = To1;
					break;
				case XTo2:
					q = MotorOn | Lamp2;
					if(t & Floor2)
						State = At2;
					else
						State = To1;
					break;		
				case At0:
					q = STATIC;
					if(t & Button1)
						State = To1;
						q = 0;
					else if(t & Button2)
						State = To2;
					else
						State = At0;
					break;
				case At1:
					q = STATIC;
					if(t & Button0)
						State = To0;
					else if(t & Button2)
						State = To2;
					else
						State = At1;
					break;
				case At2:
					q = STATIC;
					if(t & Button0)
						State = To0;
					else if(t & Button1)
						State = To1;	
						q = motorDown;
					else
						State = At2;
					break;
            }
		}while(State == To0 | To1 | To2); //stop executing once ready
            // Set the lift control bits
            PORTB = q;
            PORTA = (~q) & 0x1F;
	}
}
