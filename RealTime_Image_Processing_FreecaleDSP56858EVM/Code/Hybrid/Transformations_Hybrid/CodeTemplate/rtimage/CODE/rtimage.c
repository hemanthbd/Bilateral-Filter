/** ###################################################################
**     Filename  : rtimage.C
**     Project   : rtimage
**     Processor : 56858
**     Version   : Driver 01.11
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 3/8/2007, 8:50 PM
**     Abstract  :
**         Main module.
**         Here is to be placed user's code.
**     Settings  :
**     Contents  :
**         No public methods
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2006
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE rtimage */

/* Including used modules for compiling procedure */
#include "Cpu.h"
#include "Events.h"
#include "serial.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* Program to calculate Transformations in Hybrid */

byte inp_buffer[256];
byte  temp;
byte M=70; // Transformation Constant 'A'
byte N=110; // Transformation Constant 'B'
word r;

asm byte Transformation1_Hybrid(byte temp);
asm byte Transformation2_Hybrid(byte temp, byte N, byte M);
asm byte Transformation3_Hybrid(byte temp, byte N, byte M);


void main(void)
{
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */

  for(;;) {

r = serial_GetCharsInRxBuf();

			if (r==1) // If character is received in the receiver buffer

			{

				serial_RecvChar(&temp); // Pixel from the PC to the board
			
			/* Uncomment the function you want to run*/
			
				//temp=Transformation1_Hybrid(temp); // Negative Transformation
				//temp=Transformation2_Hybrid(temp,N,M); // Brighness/Contrast Transformation
				temp=Transformation3_Hybrid(temp,N,M); // Brighness/Contrast Transformation

				serial_SendChar(temp); // Modified Pixel sent from the board to the PC
			}
  		}
}


asm byte Transformation1_Hybrid(byte temp) // Negative Transformation; temp-> input Pixel
{ /*temp=255-temp */
	CLR A
	CLR B
	MOVE.W	Y0,A1 // Move input pixels-> A	   
	MOVE.W	#255,B 
	SUB		A,B // (255-A)->B
	MOVE.W B1,Y0 // Move B to Y0
			
	RTS		
		
}

asm byte Transformation2_Hybrid(byte temp, byte N, byte M) // Brighness/Contrast Transformation; temp-> input Pixel, N-> Transformation constant B, M-> Transformation Constant A
{
		CLR B
	    MOVE.W #255,X0
	    TFR    Y1,C // Copying contents of Y1 ('B') to C
	    ASL  C // Multiply C by two
	    MOVE.W #255,D1
	    SUB  C,D // Store 255-2C (255-2B)-> D
	    ASR  C // Divide C by two
	    
/* Run Loop for C times -> 255-B<=temp<=255 */
Loop:   SUB    Y0,X0 // Subtract input pixel from X0
		BEQ    three // If above statement is zero, goto 'three'
		ADD    Y0,X0 // else add Y0 to X0 to get back its original value
		DEC.W  X0   // Decrease X0
		DEC.W  C // Decrease C
		BNE    Loop // Break when C=0, when loop runs for C times
		
/* Run Loop for D times -> B<=temp<=255-B */
Loop2:  SUB    Y0,X0 // Subtract input pixel from X0
		BEQ    two // If above statement is zero, goto 'two'
		ADD    Y0,X0 // else add Y0 to X0 to get back its original value
		DEC.W  X0 // Decrease X0
		DEC.W  D // Decrease C
		BNE    Loop2 // Break when D=0, when loop runs for D times
		BRA    one // If the above two loops break, goto 'one' -> 0<=temp<=B

/* temp= (A*(temp-(255-B))/B) + (255-A) */		
three:  MOVE.W Y1,B1            // move the B value into B1
		MOVE.W #$FF,X0          // load a 255 value into X0 
    	SUB B,X0                // create a 255-B (in X0) -> 255-B
		SUB X0,Y0               // subtract 255-B from input and store in Y0

    // The next instruction performs a 16-bit x 16-bit signed multiplication to a 32-bit signed integer result

		IMPY.L Y0,A1,Y          // multiply the 16-bit temp-(255-B) value (in Y0) by the 16-bit A value (in A1), result in 32-bit Y -> 

    // The next 4 instructions perform a 32/16-bit unsigned integer division (the dividend and divisor are both positive)

		ASL Y                   // shift left of dividend required for integer division
    	BFCLR #$0001,SR         // clear carry bit: required for first DIV instruction
    	REP #16                 // do sixteen times for all 16 bits
    	DIV B1,Y                // divide Y1:Y0 by B, the result is in 32-bit Y
		
		MOVE.W #$FF,X0          // load a 255 value into X0 
		SUB    A,X0				// Subtract A from 255 (in X0)
    	ADD X0,Y0                // add the 16-bit A value (in A1) to the 16-bit value in Y0
    
		BRA SKIP				// Skip

/* temp = (temp-B) * (255-2A)/(255-2B) + A */
two:	MOVE.W Y1,B1            // move the B value into B1
    	SUB B,Y0                // subtract the 16-bit B value (in B1) from the 16-bit temp value (in Y0) -> input-B
    	MOVE.W #$FF,Y1          // load the 16-bit 255 value into Y1
    	ASL A                   // Multiply A by two
    	SUB A,Y1                // subtract the 16-bit A value (in A1) from the 16-bit 255 value (in Y1) -> 255-A

    // The next instruction performs a 16-bit x 16-bit signed multiplication to a 32-bit signed integer result

    	IMPY.L Y0,Y1,Y          // multiply the 16-bit temp-B value (in Y0) by the 16-bit 255-2A value (in Y0), result in 32-bit Y -> 

    	MOVE.W #$FF,X0          // load a 255 value into X0 
    	ASL B                   // Multiply B by two
    	SUB B,X0                // create a 255-B quotient (in X0) -> 255-B

    // The next 4 instructions perform a 32/16-bit unsigned integer division (the dividend and divisor are both positive)
    
    	ASL Y                   // shift left of dividend required for integer division
    	BFCLR #$0001,SR         // clear carry bit: required for first DIV instruction
    	REP #16                 // do sixteen times for all 16 bits
    	DIV X0,Y                // divide Y1:Y0 by X0, the result is in 32-bit Y
		ASR A					// divide A by 2 
    	ADD A,Y0                // add the 16-bit A value (in A1) to the 16-bit value in Y0
    
		BRA SKIP				// Skip

/* temp= (A*x)/B */		
one:    MOVE.W Y1,B1            // move the B value into B1

    // The next instruction performs a 16-bit x 16-bit signed multiplication to a 32-bit signed integer result

		IMPY.L Y0,A1,Y          // multiply A and input and store in Y 
    
    // The next 4 instructions perform a 32/16-bit unsigned integer division (the dividend and divisor are both positive)
		
		ASL    Y				// shift left of dividend required for integer division
		BFCLR #$0001,SR         // clear carry bit: required for first DIV instruction
    	REP #16                 // do sixteen times for all 16 bits
    	DIV B1,Y                // divide Y1:Y0 by B, the result is in 32-bit Y, and Y0 is the o/p

SKIP:	RTS 


}

asm byte Transformation3_Hybrid(byte temp, byte N, byte M) // Brighness/Contrast Transformation; temp-> input Pixel, N-> Transformation constant B, M-> Transformation Constant A
{
		CLR B
	    MOVE.W #255,X0
	    MOVE.W #255,D1
	    SUB  Y1,D         // Store 255-Y1 (255-2B)-> D
	    
/* Run Loop for D times -> B<=temp<=255 */
Loop:   SUB    Y0,X0  // Subtract input pixel from X0
		BEQ    two   // If above statement is zero, goto 'two'
		ADD    Y0,X0 // else add Y0 to X0 to get back its original value
		DEC.W  X0 // Decrease X0
		DEC.W  D // Decrease D
		BNE    Loop // Break when D=0, when loop runs for D times
		BRA    one // If the above loop breaks, goto 'one' ->0<=temp<=B
		
/* temp = (temp-B) * (255-A)/(255-B) + A */
two:	MOVE.W Y1,B1            // move the B value into B1
    	SUB B,Y0                // subtract the 16-bit B value (in B1) from the 16-bit temp value (in Y0) -> input-B
    	MOVE.W #$FF,Y1          // load the 16-bit 255 value into Y1
    	SUB A,Y1                // subtract the 16-bit A value (in A1) from the 16-bit 255 value (in Y1) -> 255-A

    // The next instruction performs a 16-bit x 16-bit signed multiplication to a 32-bit signed integer result

    	IMPY.L Y0,Y1,Y          // multiply the 16-bit temp-B value (in Y0) by the 16-bit 255-2A value (in Y0), result in 32-bit Y -> 

    	MOVE.W #$FF,X0          // load a 255 value into X0 
    
    	SUB B,X0                // create a 255-B quotient (in X0) -> 255-B

    // The next 4 instructions perform a 32/16-bit unsigned integer division (the dividend and divisor are both positive)
    
    	ASL Y                   // shift left of dividend required for integer division
    	BFCLR #$0001,SR         // clear carry bit: required for first DIV instruction
    	REP #16                 // do sixteen times for all 16 bits
    	DIV X0,Y                // divide Y1:Y0 by X0, the result is in 32-bit Y
    	ADD A,Y0                // add the 16-bit A value (in A1) to the 16-bit value in Y0
    
		BRA SKIP				// Skip

/* temp= (A*x)/B */		
one:    MOVE.W Y1,B1            // move the B value into B1

    // The next instruction performs a 16-bit x 16-bit signed multiplication to a 32-bit signed integer result

		IMPY.L Y0,A1,Y          // multiply A and input and store in Y 

    // The next 4 instructions perform a 32/16-bit unsigned integer division (the dividend and divisor are both positive)

		ASL    Y
		BFCLR #$0001,SR         // clear carry bit: required for first DIV instruction
    	REP #16                 // do sixteen times for all 16 bits
    	DIV B1,Y                // divide Y1:Y0 by B, the result is in 32-bit Y

SKIP:	RTS 

}


/* END rtimage */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.79]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
