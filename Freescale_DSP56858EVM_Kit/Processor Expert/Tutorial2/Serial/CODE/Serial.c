/** ###################################################################
**     Filename  : Serial.C
**     Project   : Serial
**     Processor : 56858
**     Version   : Driver 01.14
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2/16/2018, 12:38 PM
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Serial */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Serial_com.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

void main(void)
{
  /* Write your local variable definition here */
byte temp,temp1;  
 word r; 
 
/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/  
PE_low_level_init(); /*** End of Processor Expert internal initialization.  ***/ 
 
/* Infinite Loop */  
for(;;) {  /*check if a character has been received in the receive buffer */ 
r = Serial_com_GetCharsInRxBuf();  
if (r==1)  { /* A character has been received. */ 
 
/* Read char from receive buffer into temp. */ 
Serial_com_RecvChar(&temp); 

/* Send char in temp to send buffer */
 Serial_com_SendChar(temp); 
 
}  
} 
 
}

/* END Serial */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
