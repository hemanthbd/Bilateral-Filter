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

/* Program to calculate Grayscale Quantization in C */

byte inp_buffer[256];
byte  temp;
byte ShiftFactor=1; // Grayscale Quantization Shiftfactor
word r;

unsigned char Quantize(unsigned char temp,int ShiftFactor);

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



unsigned char Quantize(unsigned char temp, int ShiftFactor) // Grayscale Quantization; temp-> Input Pixel, ShiftFactor-> Quantization Factor(1,2,3,4)
{ 	if (ShiftFactor==1) // If shiftfactor=1, divide temp by two
		temp*=0.5;
    else if(ShiftFactor==2) //If shiftfactor=2, divide temp by four
        	temp*=0.25;
    else if(ShiftFactor==3) //If shiftfactor=3, divide temp by eight
        	temp*=0.125;
    else if(ShiftFactor==4) //If shiftfactor=4, divide temp by sixteen
        	temp*=0.0625;
    
    return temp;
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
