/*
* Defines parameters to control the lift.
*/
#define At0 0x00
#define At1 0x01
#define At2 0x02
#define To0 0x03
#define To1 0x04
#define To2 0x05

#define Floor0 0x08	// 0000 1000
#define Floor1 0x10	// 0001 0000
#define Floor2 0x40  // 0100 0000
#define Button0 0x01 //	0000 0001
#define Button1 0x02 //	0000 0010
#define Button2 0x04 //	0000 0100

//elevator 2 = right shifted
#define MotorOn 0x08 // 0000 1000
#define MotorDown 0x10 // 0001 0000
#define Lamp0 0x01 //	0000 0001
#define Lamp1 0x02 //	0000 0010
#define Lamp2 0x04 //	0000 0100

#define STATIC 0x00

void lift(void);
