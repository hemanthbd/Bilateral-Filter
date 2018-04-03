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

/* Program to calculate Transformations in C */

byte inp_buffer[256];
byte  temp;
byte M=70; // Transformation Constant 'A'
byte N=110; // Transformation Constant 'B'
word r;

unsigned char Transformation1_C(unsigned char temp);
unsigned char Transformation2_C(unsigned char temp,byte N, byte M);
unsigned char Transformation3_C(unsigned char temp,byte N, byte M);


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
				
				//temp=Transformation1_C(temp); // Negative Transformation
				//temp=Transformation2_C(temp,N,M); // Brighness Transformation
				//temp=Transformation3_C(temp,N,M); // Contrast Transformation

				serial_SendChar(temp); // Modified Pixel sent from the board to the PC
			}
  		}
}



unsigned char Transformation1_C(unsigned char temp) // Negative Transformation; temp-> input Pixel
{
		temp=(byte)(255-temp); // temp=255-temp
		return temp;
}

unsigned char Transformation2_C(unsigned char temp, byte N, byte M) // Brighness Transformation; temp-> input Pixel, N-> Transformation constant B, M-> Transformation Constant A
{
		if(temp>=0 && temp<=N) // If 0<=temp<=B
			temp=(byte)(((float)(M*temp))/((float)N)); // temp= (A*x)/B
		else if(temp>=N && temp<=(255-N)) // else if B<=temp<=255-B 
			temp=(byte)(((float)((255-2*M)*(temp-N)))/((float)(255-2*N))+(float)M); // temp = (temp-B) * (255-2A)/(255-2B) + A
		else if(temp>=(255-N) && temp<=255) // else if 255-B<=temp<=255 
		    temp=(byte)((float)(M*(temp-(255-N)))/((float)N)+(float)(255-M)); // temp= (A*(temp-(255-B))/B) + (255-A)
		return temp;
}

unsigned char Transformation3_C(unsigned char temp,byte N, byte M) // Contrast Transformation; temp-> input Pixel, N-> Transformation constant B, M-> Transformation Constant A
{
		if(temp>=0 && temp<=N) // If 0<=temp<=B
			temp=(byte)(((float)(M*temp))/((float)N));  // temp= (A*x)/B
		else if(temp>=N && temp<=255) // else if B<=temp<=255 
			temp=(byte)(((float)((255-M)*(temp-N)))/((float)(255-N))+(float)M); // temp = (temp-B) * (255-A)/(255-B) + A
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
