#include "Q.h"

BEGIN				//Start
STAT(0)			
	STR(0x11ffa,"%s \n");	//Format Put string 
	STR(0x11ff4,"%i \n");	//Format Put integer
	STR(0x11fee,"%c \n");	//Format Put char
	STR(0x11fe8,"%f \n");	//Format Get integer
	STR(0x11fe2,"%c \n");	//Format Get char
	STR(0x11fdc,"   \n");	//Format New_Line
CODE(0)
L 0:				
	GT(1);			//jmp to main
L 1:			//Start Main
	//Free Register
	R7 = R7 - 4; // Assign memory
	//Get R0
	R0 = 1;
	//Get R1
	R1 = 2;
	R0 = R0 + R1;
	//Free R1
	I(0x11fd8) = R0;			//Saved
	//Free R0
	R7 = R7 - 4; // Assign memory
	//Get R0
	R0 = 1;
	//Get R1
	R1 = 2;
	//Get R2
	R2 = 2;
	R1 = R1 * R2;
	//Free R2
	R0 = R0 + R1;
	//Free R1
	I(0x11fd4) = R0;			//Saved
	//Free R0
	R7 = R7 - 4; // Assign memory
	//Get R0
	R0 = 1;
	//Get R1
	R1 = 2;
	//Get R2
	R2 = 2;
	R1 = R1 * R2;
	//Free R2
	//Get R2
	R2 = 2;
	R1 = R1 / R2;
	//Free R2
	R0 = R0 + R1;
	//Free R1
	I(0x11fd0) = R0;			//Saved
	//Free R0
	R7 = R7 - 4; // Assign memory
	//Get R0
	R0 = 1;
	//Get R1
	R1 = 2;
	R0 = R0 + R1;
	//Free R1
	//Get R1
	R1 = 2;
	R0 = R0 * R1;
	//Free R1
	I(0x11fcc) = R0;			//Saved
	//Free R0
	R7 = R7 - 4;			//Save space for register R0
	I(R7) = R0;			//R0 saved
	R7 = R7 - 4;			//Save space for register R1
	I(R7) = R1;			//R1 saved
	R7 = R7 - 4;			//Save space for register R2
	I(R7) = R2;			//R2 saved
	// Start of Print variable
	R0 = 2;			//Return label
	R1 = 0x11ff4;			//Format int address
	R2 = I(0x11fd8);			//Static variable value
	GT(putf_);			//Print variable
L 2:				
	// End of Print variable
	R2 = I(R7);			//R2 recovered
	R7 = R7 + 4;			//Free space for register R2
	R1 = I(R7);			//R1 recovered
	R7 = R7 + 4;			//Free space for register R1
	R0 = I(R7);			//R0 recovered
	R7 = R7 + 4;			//Free space for register R0
	R7 = R7 - 4;			//Save space for register R0
	I(R7) = R0;			//R0 saved
	R7 = R7 - 4;			//Save space for register R1
	I(R7) = R1;			//R1 saved
	R7 = R7 - 4;			//Save space for register R2
	I(R7) = R2;			//R2 saved
	// Start of Print variable
	R0 = 3;			//Return label
	R1 = 0x11ff4;			//Format int address
	R2 = I(0x11fd4);			//Static variable value
	GT(putf_);			//Print variable
L 3:				
	// End of Print variable
	R2 = I(R7);			//R2 recovered
	R7 = R7 + 4;			//Free space for register R2
	R1 = I(R7);			//R1 recovered
	R7 = R7 + 4;			//Free space for register R1
	R0 = I(R7);			//R0 recovered
	R7 = R7 + 4;			//Free space for register R0
	R7 = R7 - 4;			//Save space for register R0
	I(R7) = R0;			//R0 saved
	R7 = R7 - 4;			//Save space for register R1
	I(R7) = R1;			//R1 saved
	R7 = R7 - 4;			//Save space for register R2
	I(R7) = R2;			//R2 saved
	// Start of Print variable
	R0 = 4;			//Return label
	R1 = 0x11ff4;			//Format int address
	R2 = I(0x11fd0);			//Static variable value
	GT(putf_);			//Print variable
L 4:				
	// End of Print variable
	R2 = I(R7);			//R2 recovered
	R7 = R7 + 4;			//Free space for register R2
	R1 = I(R7);			//R1 recovered
	R7 = R7 + 4;			//Free space for register R1
	R0 = I(R7);			//R0 recovered
	R7 = R7 + 4;			//Free space for register R0
	R7 = R7 - 4;			//Save space for register R0
	I(R7) = R0;			//R0 saved
	R7 = R7 - 4;			//Save space for register R1
	I(R7) = R1;			//R1 saved
	R7 = R7 - 4;			//Save space for register R2
	I(R7) = R2;			//R2 saved
	// Start of Print variable
	R0 = 5;			//Return label
	R1 = 0x11ff4;			//Format int address
	R2 = I(0x11fcc);			//Static variable value
	GT(putf_);			//Print variable
L 5:				
	// End of Print variable
	R2 = I(R7);			//R2 recovered
	R7 = R7 + 4;			//Free space for register R2
	R1 = I(R7);			//R1 recovered
	R7 = R7 + 4;			//Free space for register R1
	R0 = I(R7);			//R0 recovered
	R7 = R7 + 4;			//Free space for register R0
	R0=0;			//Succesful state
	GT(-2);			//Finish
END
