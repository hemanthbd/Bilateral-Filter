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

//////////////////Program to implement Thresholding Functions in C/////////////////////////////

byte inp_buffer[256];
byte  temp;
word r;
byte T=80; // Threshold
byte L=80; // Lower Threshold
byte H=120; // Upper Threshold

unsigned char Thresholding1_C(unsigned char temp, int T);
unsigned char Thresholding2_C(unsigned char temp, int L, int H);
unsigned char Thresholding3_C(unsigned char temp, int T);


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
		/* Uncomment the function you want to call */

				//temp=Thresholding1_C(temp,T); 	// Global Thresholding
				//temp=Thresholding2_C(temp,L,H);	// Band Thresholding
				//temp=Thresholding3_C(temp,T);		// Semi-Thresholding
			
				serial_SendChar(temp); // Modified Pixel sent from the board to the PC
			}
  		}
}

unsigned char Thresholding1_C(unsigned char temp, int T) // Global Thresholding; temp->Input Pixel, T-> Threshold
{
		if(temp>=T) 	// If Pixel is greater than T, make it 255
			temp=255;
		else        	// else make it 0
			temp=0;
		return temp;
}

unsigned char Thresholding2_C(unsigned char temp,int L, int H) // Band Thresholding; temp->Input Pixel, L-> Lower Threshold, H-> Upper Threshold
{
		if(temp>=L && temp<=H) // If Pixel lies in-between L and H, make it 255
			temp=255;
		else
			temp=0;            // else make it 0
		return temp;
}

unsigned char Thresholding3_C(unsigned char temp, int T) // Semi-Thresholding; temp->Input Pixel, T-> Threshold
{
		if(temp>=T) 	// If Pixel is greater than T, keep it
			temp=temp;
		else
			temp=0; 	// else make it 0
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
