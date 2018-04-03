/** ###################################################################
**     Filename  : Filter.C
**     Project   : Filter
**     Processor : 56858
**     Version   : Driver 01.05
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 12/17/03, 8:55 PM
**     Abstract  :
**         Main module.
**         Here is to be placed user's code.
**     Settings  :
**     Contents  :
**         No public methods
**
**     Copyright Freescale Semiconductor, Inc. All Rights Reserved.
** ###################################################################*/
/* MODULE Filter */

/* Including used modules for compilling procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "Inhr1.h"
#include "Codec.h"
#include "Inhr2.h"
#include "Inhr3.h"
#include "Inhr4.h"
#include "Inhr5.h"
#include "Inhr6.h"
#include "EInt1.h"
#include "EInt2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#define FIFO_SIZE   32
#define NUM_SAMPLES 2
#define NUM_BYTES   (2*NUM_SAMPLES)
#define SIZE 23






/*******************************************************************************
*
* Module:
*    main()
*
* Description:
*    This function is the main function of the Codec demo.
*
*******************************************************************************/
void main(void)
{


  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Set up LEDs */
  LED1_On();
  while(1)
  {
  	
  }  /* Infinite loop, waiting for external interrupt */
  /* The executive loop just toggles the LED depending on the number of
	 Samples received from the Codec.  Meanwhile, all loopback is done
	 in the ISRs. */
 
}


/* END Filter */
/*
** ###################################################################
**
**     This file was created by Processor Expert
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
