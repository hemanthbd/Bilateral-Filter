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

/* Program to perform Histogram Equalization in C */

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

void main(void)
{
    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/

    for(;;)
    {
        clear_histograms(); // Initialize histogram value to 0
 		input_output_images();// Get your pixel values from input frame vector		
        calculate_histogram(); // Calculate histogram for the frame       
		map_levels(); // Map the intensities using CDF
        transform_image(); // Transform the image according to the new histogram through equalization
        

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
    for(i=0; i<size; i++)                  // Run for loop for 256 levels
    { hist_org[i]=0;                       // Initialize all values in the histogram to 0
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

Input values:   The elements of the globally declared byte array, image_org.
Output values:  The elements of the globally declared integer array, hist_org.

*/

void calculate_histogram()
{
    int i,temp ;
    for(i=0; i<N1; i++)   // Run a for loop for every pixel in a frame
    { temp=image_org[i]; // temp holds current image pixel
     hist_org[temp]++;  //Pointer shifts to the respective pixel value in the histogram and increments its count  
    
    
    }
}



/*
"map_levels" is a function that maps 8-bit video grayscale levels represented by an array
index to a new value stored as an element in the array, mapped_levels.  This function
calls another function, cdf().  A function value is not returned.

Input values:   The elements of the globally declared int array, hist_org.
Output values:  The elements of the globally declared byte array, mapped_levels.
*/

void map_levels()
{
    int w;
    float sum=0;
    for(w=0; w<size; w++) // Run a for loop for 256 levels in the histogram
    { sum+= hist_org[w]; //store the current cdf in sum
    mapped_levels[w]= (byte)(255*sum/N1); //the new intensity value is 255*sum/N
     
     }
        
    
}



/*

"transform_image" is a function that transforms the video brightness levels of a
globally declared array, image_org, to an output array, image_equ.  A third globally
declared array, mapped_levels, is used to make the transformation by mapping a byte
address to a byte value.  A function value is not returned.

Input values:   The elements of the globally declared byte array, image_org.
                The elements of the globally declared byte array, mapped_levels.
Output values:  The elements of the globally declared byte array, image_equ.
*/

void transform_image()
{
    int i;
    for(i=0; i<N1; i++)
    { image_equ[i]=mapped_levels[image_org[i]]; // Map the current intensity value to the respective ones' in the original frame, and that value becomes your histogram equalized intensity
 
       
    }
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
