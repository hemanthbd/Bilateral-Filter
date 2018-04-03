/** ###################################################################
**     Filename  : Combo.C
**     Project   : Combo
**     Processor : 56858
**     Version   : Driver 01.14
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2/16/2018, 2:18 PM
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Combo */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED0.h"
#include "Serial_com.h"
#include "Button.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "LED5.h"
#include "TI1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

void main(void)
{
  byte temp;  
 word r; 
 /*LED0_ClrVal();
LED1_ClrVal();
LED2_ClrVal();
LED3_ClrVal();
LED4_ClrVal();
LED5_ClrVal();
*/
/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/  
PE_low_level_init(); /*** End of Processor Expert internal initialization.  ***/ 

/* Infinite Loop */  
for(;;) {  /*check if a character has been received in the receive buffer */ 
r = Serial_com_GetCharsInRxBuf();  
if (r==1)  { /* A character has been received. */ 

/* Read char from receive buffer into temp. */ 
Serial_com_RecvChar(&temp); 

/***** This is for if a Value is sent to the board(1-6), the respective LEDS(0-5) turn on while the rest, off.
if(temp=='1') // If the character sent is 1, switch on LED0, and turn the rest off.
{ LED0_SetVal();
LED1_ClrVal();
LED2_ClrVal();
LED3_ClrVal();
LED4_ClrVal();
LED5_ClrVal();
}
else if(temp=='2') // If the character sent is 2, switch on LED1, and turn the rest off.
{LED0_ClrVal();
LED1_SetVal();
LED2_ClrVal();
LED3_ClrVal();
LED4_ClrVal();
LED5_ClrVal();
}
else if(temp=='3') // If the character sent is 3, switch on LED2, and turn the rest off.
{LED0_ClrVal();
LED1_ClrVal();
LED2_SetVal();
LED3_ClrVal();
LED4_ClrVal();
LED5_ClrVal();
}
else if(temp=='4') // If the character sent is 4, switch on LED3, and turn the rest off.
{LED0_ClrVal();
LED1_ClrVal();
LED2_ClrVal();
LED3_SetVal();
LED4_ClrVal();
LED5_ClrVal();
}
else if(temp=='5') // If the character sent is 5, switch on LED4, and turn the rest off.
{LED0_ClrVal();
LED1_ClrVal();
LED2_ClrVal();
LED3_ClrVal();
LED4_SetVal();
LED5_ClrVal();
}
else if(temp=='6') // If the character sent is 6, switch on LED5, and turn the rest off.
{LED0_ClrVal();
LED1_ClrVal();
LED2_ClrVal();
LED3_ClrVal();
LED4_ClrVal();
LED5_SetVal();
}

******/

/***This is if the user sends (1-4), the respective blinking rate (0.25,0.5,0.75,1sec) gets activated for LED0
if(temp=='1')
{ TI1_SetPeriodMode(0);// If the user sends ‘1’, blink-rate-0.25sec

}
else if(temp=='2') // If the user sends ‘2’, blink-rate-0.50sec

{TI1_SetPeriodMode(1);


}
else if(temp=='3') // If the user sends ‘3’, blink-rate-0.75sec

{TI1_SetPeriodMode(2);



}
else if(temp=='4')  // If the user sends ‘4’, blink-rate-1.00sec

{TI1_SetPeriodMode(3);


 
}***/

/* Send char in temp to send buffer */
 Serial_com_SendChar(temp);
}  
} 
 
}

/* END Combo */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
