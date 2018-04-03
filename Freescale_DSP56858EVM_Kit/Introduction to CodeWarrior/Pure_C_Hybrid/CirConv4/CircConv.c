
void multiply (int a [] , int b[], int c[], const length)
{
	int i;

	for (i=0; i< length; i ++)
	c[i] = a [i] * b[i];  // multiply two numbers
	 

}
asm void Hmultiply (int a [] , int b[], int c[], const length)

{
	// a -> r2, b -> r3, c -> r4, length -> y0
		
		DO	Y0, END_LOOP

		MOVE.W	X:(R2)+,C1
		MOVE.W 	X:(R3)+,Y1	
		IMPY.W 	C1,Y1,A
		MOVE.W	A1, X:(R4)+
END_LOOP:

		RTS
}


asm int Hsum (int a[], const length)

{

// pointer to the array stored in R2 (Chapter 6 pages 115,116 - C for DSP56800E)
// length stored in register Y0
// returned value stored also  in Y0

	MOVEU.W	Y0, R0
	ADDA	R2,R0
	MOVE.W	#0000,Y0
LOOP:
	MOVE.W	X:(R2)+, X0
	ADD		X0, Y0
	CMPA	R2,R0
	BLE 	DONE
	BRA		LOOP
DONE:
	RTS
	

}



int sum (int a[], const length)
{
	int i, sum;
	sum =0;
	for (i = 0;i<length;i++)  // sum element
		sum = sum + a[i]; 

	return sum;

}

void swap (int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}



void circflip(int arr[], const length)

{
	int j,i;
	j = length-1;
	for (i=1;i<length;i++)
		{
		swap(&arr[i],&arr[j]);
		
		if (i>=j)
		{break;}
		j = j-1;
		}

}

asm void Hcircflip (int arr[], const length)

{
	DEC.W 	Y0
	MOVE.W	Y0, R1
	ADDA	R2,R1
	ADDA	#1,	R2
SWAP_LOOP:
	CMPA	R2,R1
	BLE		DONE
	MOVE.W	X:(R2),X0
	MOVE.W	X:(R1),Y0
	MOVE.W  X0,X:(R1)-
	MOVE.W	Y0,X:(R2)+
	BRA		SWAP_LOOP
DONE:

	rts


}
void circshift(int arr[], const length)
{
	// circular rotate array by one
	int i, s,temp;
	
	
		temp = arr[length- 1];
		for (i= length - 1;i > 0;i--)
		{arr[i]=arr[i-1];
		}
		arr[0] = temp;
}


asm void Hcircshift(int arr[], const length)

{	
	DEC.W	Y0
	MOVE.W	Y0,R3
	ADDA	R3, R2
	MOVE.W	X:(R2), X0
	ADDA	#-1,R2,R1

	DO	Y0, End_Shift
	MOVE.W	X:(R1)-,C1
	MOVE.W	C1,X:(R2)-
	

End_Shift:


	MOVE.W	X0, X:(R2)

	RTS
}



#define   SIZE 8	// Defining Array size


//Prototypes for functions used
int sum (int [],int);
void multiply(int [],int[],int[],const);



int x[SIZE] = {1,1,1,1,1,0,0,0}; // Input array 1 
int y [SIZE] = {0,0,0,1,1,1,1,1}; // Input array 2
int p[SIZE]; // Product array
int s; //Summation result
int arr[SIZE]; // Final Array after Circular Convolution
int main(void)
{ int count=0; // Initializing to zero. This is used as the index for the final array, arr[SIZE}
	Hcircflip(y, SIZE); // Circular flip the y array and store it in the same array
	do                 // Start a do-while loop
	{
	Hmultiply(x,y,p, SIZE); // Dot product of each value of the x array and circular flipped array y, and store in p array
	s = Hsum (p, SIZE); // Summation of all the values in p and store in a variable 's'
	arr[count]=s; // Store the 's' variable value in an array, arr, corresponding to how many times 'arr' is being invoked-taken care by the 'count' variable.
	count++; // Increment count, so that next time, 's' will be stored in that corresponding incremented count index in arr.
	Hcircshift(y,SIZE); // The circular flipped array,y, is now circular shifted through mod operation
	}while(count<SIZE); // Condtion for the do-while loop- Breaks if count becomes greater than SIZE
	return(0);
}





