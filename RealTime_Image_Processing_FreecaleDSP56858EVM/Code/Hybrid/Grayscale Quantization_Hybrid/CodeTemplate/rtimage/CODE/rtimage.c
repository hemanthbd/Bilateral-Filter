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

/* Program to calculate Grayscale Quantization in Hybrid */

byte inp_buffer[256];
byte  temp;
byte ShiftFactor=4; // Grayscale Quantization Shiftfactor
word r;

asm byte Quantize(byte temp, byte ShiftFactor);

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

				serial_RecvChar(&temp);// Pixel from the PC to the board

				temp=Quantize(temp,ShiftFactor); // Grayscale Quantization
				
				serial_SendChar(temp); // Modified Pixel sent from the board to the PC
			}
  		}
}



asm byte Quantize(byte temp, byte ShiftFactor) // Grayscale Quantization; temp-> Input Pixel, ShiftFactor-> Quantization Factor(1,2,3,4)
{ 	CLR A
	CLR B
	MOVE.W  Y1,B1 // Move ShiftFactor->B
	MOVE.W  #1,X0 
	MOVE.W  #2,C1
	MOVE.W  #3,A1
	SUB		X0,B // Subtract X0 from B
	BEQ		Shiftone // If above statement is zero, goto 'Shiftone'
	ADD		X0,B // else Add X0 to B to get B back to its original value
	SUB     C,B  // Subtract C from B
	BEQ		Shifttwo // If above statement is zero, goto 'Shifttwo'
	ADD     C,B // else Add C to B to get B back to its original value
	SUB		A,B // Subtract A from B
	BEQ     Shifthree  // If above statement is zero, goto 'Shiftthree'
	ADD     A,B // else Add C to B to get B back to its original value
	BRA		Shiftfour // If all the above statements fail, goto 'Shiftfour'
			   
Shiftone: 	ASR		Y0 // Right-shift your input pixel once, ie, temp/2
			BRA		SKIP // Skip

Shifttwo:   REP		#2 // Repeat below statement 2 times
			ASR		Y0 // Right-shift your input pixel , ie, temp/4
			BRA		SKIP
			
Shifthree:	REP		#3 // Repeat below statement 3 times
			ASR		Y0 // Right-shift your input pixel, ie, temp/8
			BRA		SKIP
			
Shiftfour:	REP		#4 // Repeat below statement 3 times
			ASR		Y0 // Right-shift your input pixel, ie, temp/16
			

SKIP:		RTS	// Skip
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
