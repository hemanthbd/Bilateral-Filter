/** ###################################################################
**     Filename  : Filter_C_fixed.C
**     Project   : Filter_C_fixed
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
/* MODULE Filter_C_fixed */

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
#include "IRQA.h"
#include "IRQB.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#define FIFO_SIZE   32
#define NUM_SAMPLES 2
#define NUM_BYTES   (2*NUM_SAMPLES)
#define SIZE 24
int j, index;
signed long y;
int sample_array[SIZE]={0};

volatile UWord16 LoopCount = 0;
volatile Word16 pSamples[FIFO_SIZE];
asm int HFilter(int[],int[],int);
/* Filter coefficients */
int h[SIZE]={-39, 159, -36, -337, 486, 185, -1205, 947, 1413, -3745, 1289, 17300, 17300, 1289, -3745, 1413, 947, -1205, 185, 486, -337, -36, 159, -39};  

/*******************************************************************************
*
* Module:
*    main()
*
* Description:
*    This function is the main function of the Codec demo.
*
*******************************************************************************/


asm int HFilter(int a[], int b[], int c)
{
	
//	MOVEU.W Y0,R0 ;//get pointer to ARR1
//	MOVEU.W Y1,R3 ;//get pointer to ARR2
	CLR A // clear Accumulator A
	MOVEU.W R2,R0
	MOVE.W X:(R2)+,Y0 //read first element of sample_array into Y0
	MOVE.W X:(R3)+,X0 //read first elementof ARR2 into X0
	REP #24 //repeat next instruction 24 times
	MAC Y0,X0,A X:(R0)+,Y0 X:(R3)+,X0 
	MOVE.W A1,Y0 
	
	RTS


//; Multiply Y0*X0 + A -> A, in
//;parallel store content of memory
//;pointed by R0 and R3 into Y0 and
//;X0 respectively and post
//;increment the two pointers

}




void main(void)
{
  Word16 samples;
  Word16 i;
  word   Rcv, Snd;


  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Set up LEDs */
  LED1_On();

  /* The executive loop just toggles the LED depending on the number of
	 Samples received from the Codec.  Meanwhile, all loopback is done
	 in the ISRs. */
  while(1)
  {
    samples = 0;
  
	while (samples < NUM_SAMPLES) {
      Codec_Read((void*)&pSamples[samples], NUM_SAMPLES-samples, &Rcv);
      samples += Rcv;
    }

	samples = 0;
	

		
		for (j=SIZE-1; j>0; j--)	            
		{
			sample_array[j]=sample_array[j-1];		
		}
	
		sample_array[0] = pSamples[samples];    

	//	y = 0;									
		
	/*	for (j=0; j<SIZE; j++)
		{
	
			y += ((long)sample_array[j]*(long)h[j]); 
		}
	*/

	if(IRQA_GetVal() || y == 1)
	{
	 y = 1;
	}
	if(IRQB_GetVal() || y == 2)
	{
	 y = 2;
	}

		
		if(y == 1)
	{
	pSamples[samples]= HFilter(sample_array,h,SIZE);
	}
	
		 
	//	pSamples[samples] = (int) (y>>15);				

	while (samples < NUM_SAMPLES) {
	  Codec_Write((void*)&pSamples[samples], NUM_SAMPLES-samples, &Snd);
	  samples += Snd;
	}

    LoopCount++;

    if (LoopCount > 1500) {
      LoopCount = 0;
      LED1_Toggle();
    }
  }
}


/* END Filter_C_fixed */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 03.39 for
**     the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
