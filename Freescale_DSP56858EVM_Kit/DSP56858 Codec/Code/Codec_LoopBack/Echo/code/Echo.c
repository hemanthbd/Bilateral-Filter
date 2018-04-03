/** ###################################################################
**     Filename  : Codec_LoopBack.C
**     Project   : Codec_LoopBack
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
**     Freescale Inc.
**     (c) Copyright 2003 Freescale, Inc.
**     ALL RIGHTS RESERVED.
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2003
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE Codec_LoopBack */

/* Including used modules for compilling procedure */
#include "Cpu.h"
#include "LED1.h"
#include "Inhr1.h"
#include "Codec.h"
#include "Inhr2.h"
#include "intrinsics_56800E.h"
#include "Inhr3.h"
#include "Inhr4.h"
#include "Inhr5.h"
#include "Inhr6.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#define FIFO_SIZE   32
#define NUM_SAMPLES 2
#define NUM_BYTES   (2*NUM_SAMPLES)
#define BUFSIZE 4096

volatile Word16 buffer[BUFSIZE]={0};
volatile UWord16 LoopCount = 0;
volatile Word16 pSamples[FIFO_SIZE];
int cnt=0;

asm int HEcho(int, int, int);
/*******************************************************************************
*
* Module:
*    main()
*
* Description:
*    This function is the main function of the Codec demo.
*
*******************************************************************************/

asm int HEcho(int a, int b, int c)
{
	MPY A1,Y1,Y1;// multiply c and b and store the result in B
	ADD Y1, Y0; // Add b and a and store in a(Y0)
	RTS;
}



void main(void)
{
  Word16 samples;
  Word16 i;
  word   Rcv, Snd;
  Word16	attenuation = 16384;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Set up LEDs */
  LED1_On();
    for (i=0;i<BUFSIZE;i++)
	    {buffer[i] = 0;
	    }
    for (i=0; i<FIFO_SIZE/2; i++) {
        pSamples[i] = 10;
    }
  /* The executive loop just toggles the LED depending on the number of
	 Samples received from the Codec.  Meanwhile, all loopback is done
	 in the ISRs. */
  while(1)
  {
    samples = 0;
    /* Read speech samples from the codec. Returns number of bytes read */
	while (samples < NUM_SAMPLES) {
      Codec_Read((void*)&pSamples[samples], (NUM_SAMPLES-samples), &Rcv);
      samples += (Rcv);
    }

	samples = 0;
	cnt = cnt%BUFSIZE;
		
		for (i=0;i<NUM_SAMPLES/2;i++)
		{	//		buffer[cnt+i] = pSamples[i]+ mult(attenuation,buffer[cnt+i]); this will work too
		//	buffer[cnt+i] = mac_r(((long)pSamples[i])<<16, attenuation,buffer[cnt+i]);//Comment
		buffer[cnt+i] = HEcho(pSamples[i], attenuation, buffer[cnt+i]);
			}


    /* Write speech samples to the codec. Returns number of bytes written */
	while (samples < NUM_SAMPLES) {
	  Codec_Write((void*)&buffer[cnt], (NUM_SAMPLES-samples), &Snd);
	  samples += (Snd);
	}

    LoopCount++;
cnt=cnt+(NUM_SAMPLES/2);
    if (LoopCount > 1500) {
      LoopCount = 0;
      LED1_Toggle();
    }
  }
}


/* END Codec_LoopBack */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 03.39 for
**     the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
