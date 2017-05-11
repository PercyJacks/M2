#include "FreeRTOS.h"
#include "task.h"
#include "lift.h"


/*

Remember T0 is bottom floor, T2 is top and T1 or TM is the middle which is not used.


This task spends most of its time sleeping, so the infinite loop does not stop other things working.

*/

ISR(INT0_vect){ //Catch interrupt 0
t = PINC; // read lift sensors from port B
        t = (~t) & 0x7F; // Lift is negative logic
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
			case To2:
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
            // Set the lift control bits
            PORTB = q;
            PORTA = (~q) & 0x1F;
}


void lift(void){
    unsigned char t, q;
    unsigned char State; // Start going down.
    PORTA = 0xFF;
    State = To0;
	MCUCR = MCUCR | 0x03;
	GICR = GICR | 0x40; // Enable interupt 0
	for(;;)
	{
		//contents fo for loop moved to interrupt, just run for loop so function doesnt return.
	}
}
