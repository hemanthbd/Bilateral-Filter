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

//////////////////Program to implement Thresholding Functions in Hybrid/////////////////////////////

byte inp_buffer[256];
byte  temp;
word r;
byte T=80; // Threshold
byte L=80; // Lower Threshold
byte H=120; // Upper Threshold


asm byte Thresholding1_Hybrid(byte temp, byte T);
asm byte Thresholding2_Hybrid(byte temp,byte L,byte H);
asm byte Thresholding3_Hybrid(byte temp,byte T);


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

				//temp=Thresholding1_Hybrid(temp,T); // Global Thresholding
				//temp=Thresholding2_Hybrid(temp,L,H); // Band Thresholding
				//temp=Thresholding3_Hybrid(temp,T); // Semi-Thresholding
				
				serial_SendChar(temp); // Modified Pixel sent from the board to the PC
			}
  		}
}



asm byte Thresholding1_Hybrid(byte temp, byte T) // Global Thresholding; temp-> input Pixel, T->Threshold
{
		CLR A
		CLR B
		MOVE.W	Y0,A1 // Move temp->A	   
	    MOVE.W #255,B 
		TFR B,C  // Copy contents of B to C
		SUB Y1,C // (255-T)->C
/*Loop that runs C times */
Loop:	SUB		A,B  // Subtract pixel value from B
		BEQ     white // If zero, goto 'white'
		ADD		A,B	// else add A to B to bring it back to its original value	
		DEC.W	B // Decrease B
		DEC.W   C // Derease C
		BNE     Loop // Break when C=0, ie, Loop runs C times.
		BRA		black // If loop breaks, goto 'black'
white:	MOVE.W	#255,Y0 // Move 255 to Y0
		BRA		SKIP // Skip
black:	MOVE.W	#0,Y0 // Move 0 to Y0
SKIP:	RTS	 // Skip
				
}

asm byte Thresholding2_Hybrid(byte temp, byte L , byte H) // Band Thresholding; temp->Input Pixel, L-> Lower Threshold, H-> Upper Threshold
{
		CLR B
		MOVE.W	Y0,D1 // Move input pixel -> D
	    MOVE.W  A1,B // Move Higher limit -> B
		TFR   B,C // Copy contents of B -> C
		SUB   Y1,C // H-L -> C 
/*Loop that runs C times */		
Loop:	SUB		D,B // Subtract pixel value from B
		BEQ     white // If zero, goto 'white'
		ADD		D,B	// else add D to B to bring it back to its original value	
		DEC.W	B // Decrease B
		DEC.W   C // Decrease C
		BNE     Loop // Break when C=0,ie, Loo runs C times
		BRA		black // If loop breaks, goto 'black'
white:	MOVE.W  #255,D // Move 255 to D
		MOVE.W	D1,Y0 // Move D to Y0
		BRA		SKIP // Skip
black:	MOVE.W	#0,Y0 // Move 0 to Y0
SKIP:	RTS	 // Skip
					
}

asm byte Thresholding3_Hybrid(byte temp, byte T) // Semi Thresholding; temp-> input Pixel, T->Threshold
{
		CLR A
		CLR B
	    MOVE.W	Y0,A1 // Move temp->A	   
	    MOVE.W #255,B
		TFR B,C // Copy contents of B to C
		SUB Y1,C // (255-T)->C
/*Loop that runs C times */		
Loop:	SUB		A,B // Subtract pixel value from B
		BEQ     same // If zero, goto 'same'
		ADD		A,B	// else add A to B to bring it back to its original value	
		DEC.W	B // Decrease B
		DEC.W   C // Derease C
		BNE     Loop // Break when C=0, ie, Loop runs C times.
		BRA		black // If loop breaks, goto 'black'
same:	MOVE.W	A1,Y0 // Move A1 (input pixel) to Y0
		BRA		SKIP // Skip
black:	MOVE.W	#0,Y0 // Move 0 to Y0
SKIP:	RTS	 // Skip
		
	
		

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
