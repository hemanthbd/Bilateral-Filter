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

/* Program to perform Histogram Equalization in Hybrid */

#define N1 (96*128)              // 96 lines of 128 pixels = 12,288 pixels total
#define size 256                // 256 gray-scale brightness levels

void clear_histograms();
void input_output_images();
void calculate_histogram();
void map_levels();
void transform_image();

byte image_org[N1];
byte image_equ[N1];
int hist_org[size] = {0};
byte mapped_levels[size];

asm void Hcalculate_histogram(int* ,byte* ,int);
asm void Hmap_levels(byte* ,int* ,int ,int );
asm void  Htransform_image(byte* ,byte* ,byte* ,int );


void main(void)
{
    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/

    for(;;)
    {
        clear_histograms(); // Initialize histogram value to 0
 		input_output_images(); // Get your pixel values from input frame vector		
        Hcalculate_histogram(hist_org,image_org,N1); // Calculate histogram for the frame
        Hmap_levels(mapped_levels,hist_org,N1,size); // Map the intensities using CDF
        Htransform_image(image_equ,image_org,mapped_levels,N1); // Transform the image according to the new histogram through equalization

    }
}


/*

"clear_histograms" is a function that sets each element of the globally declared integer
array to zero.  A function value is not returned.

Input values:   The elements of the globally declared integer array hist_org.
Output values:  The elements of the integer array are set to zero.

*/

void clear_histograms()
{
    int i ;
    for(i=0; i<size; i++)                 // Run for loop for 256 levels
    { hist_org[i]=0; 					// Initialize all values in the histogram to 0
    }
}


/*

"input_output_images" is a function that receives asynchronous SCI characters and saves
them  sequentially to the global byte array, image_org.  At the same time, this function
transmits characters sequentially stored in another byte array, image_equ.  A complete
frame of video pixels is received and transmitted.  The number of pixels in a frame is
globally defined as "N1".  A function value is not returned.

Input values:   The elements of the globally declared byte array image_equ are
                sequentially transmitted serially via the SCI.
Output values:  The characters serially received via the SCI are sequentially stored in
                the globally declared byte array image_org.

*/

void input_output_images()
{ // no need to edit this function. Use as is.
    word r;
    int i;
    for(i=0; i<N1;)                      // do this for each pixel in one frame
    {
        r = serial_GetCharsInRxBuf();   // check for a received SCI character

        if (r==1) // If character is received in the receiver buffer
        {

            // get the received serial character and store this pixel in the image_org array
            serial_RecvChar(&image_org[i]);
            
            // send a character stored as a pixel in the image_equ array via the SCI
            serial_SendChar(image_equ[i]);

            // increment the for-loop counter here if successful
            i++;
        }
    }
}


/*

"calculate_histogram" is a function that counts the frequency of the occurance of each
video level stored in the globally declared byte array, image_org.  The number of pixels
processed from the array is set by the globally defined constant, N1.  A function value
is not returned.

Input values:   The elements of the globally declared byte array, image_org passed as a pointer .
Output values:  The elements of the globally declared integer array passed as a pointer, hist_org.

*/



asm void Hcalculate_histogram(int* hst, byte* img, int sz) // *hist->hist_org,*img-image_org,sz-N1
{	
	DO		Y0,Loop // DO while loop for 'N' times
	MOVEU.BP	X:(R3)+, X0 //Moves first byte value of R3 ('image_org') into X0
	CLR		A     // Clear A
	MOVE.W  R2,A // Moves Address R2 ('first position of hist_org') to A
	ADD		X0,A // Add address and value to A, and store in A
	MOVEU.W	A,R0 // Move A to R2
	INC.W	X:(R0) // Increment the value of R2 at that position   
Loop:
	rts 
	}



/*
"map_levels" is a function that maps 8-bit video grayscale levels represented by an array
index to a new value stored as an element in the array, mapped_levels.  This function
calls another function, cdf().  A function value is not returned.

Input values:   The elements of the globally declared int array, hist_org,passed as a pointer ..
Output values:  The elements of the globally declared byte array, mapped_levels,passed as a pointer ..
*/



asm void Hmap_levels(byte* map, int* hst , int z, int p) //*hist->hist_org,*map-mapped_levels,z->N1,p->size
{
	CLR     A
	MOVE.W  Y1,D // Move Size to D
	MOVE.W  Y0,B // Move N1 to B
	DO		D,Loop // DO while loop for 'Size' times	
	MOVE.W	X:(R3)+,X0 // Move value of the first pointer address of histogram to X0
	ADD		X0,A // Add X0 to A -> CDF
	MOVE.W  #$FF,C1 // Move 255->C
	IMPY.L 	C1,A1,Y // Multiply 255 with A (CDF) and store in Y (Y=255*sum)
    ASL     Y     // Left shift Y for division
    BFCLR 	#$0001,SR           // clear carry bit: required for first DIV instruction
    REP 	#16                 // do sixteen times for all 16 bits
    DIV 	B1,Y                // divide Y by B, the result is in 32-bit Y (Y=Y/N)
	MOVE.BP Y0,X:(R2)+ // Move byte pointer stored in Y0 to pointer address in Mapped register (R2) and increment 

Loop:
	
		RTS	
}



/*

"transform_image" is a function that transforms the video brightness levels of a
globally declared array, image_org, to an output array, image_equ.  A third globally
declared array, mapped_levels, is used to make the transformation by mapping a byte
address to a byte value.  A function value is not returned.

Input values:   The elements of the globally declared byte array, image_org,passed as a pointer.
                The elements of the globally declared byte array, mapped_levels,passed as a pointer.
Output values:  The elements of the globally declared byte array, image_equ,passed as a pointer.
*/



asm void Htransform_image(byte* eq,byte* imgpix,byte* mapp, int num) //*eq->image_equ,*mapp-mapped_levels,imgpix->image_org,num->N1
{	
	DO	Y0,Loop // Do while for N1 times
	MOVEU.BP X:(R3)+,X0 // Move value of byte pointer of image array to X0
	CLR     A
	MOVE.W  R4,A // Move current address of mapped address to A
	ADD  	X0,A // Add address stored in A to the value of the current address of the image array, and store the result in A
	MOVEU.W A,R0 // Move A-> R0
	MOVEU.BP X:(R0),Y1 // Move byte pointer of R0-> Y1
	MOVE.BP  Y1,X:(R2)+ // Move the result to the first address of image_equ register (R2) and increment the pointer of R2
	
Loop: RTS

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
