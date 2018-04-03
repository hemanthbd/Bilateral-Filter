	
	
	
	
	
; -------------------------------------------------------
; 	
;	Arizona State University
;	EE498 - Real Time DSP
;	
; 	
; -------------------------------------------------------
 	
	
LENGTH	EQU		8
		
	section rtlib
	org x:
	
X_BUF DC 	1,1,1,1,1,0,0,0 ;Initializing input array , X_BUF
Y_BUF DS 	8 
ARR_BUF DC 	0,0,0,1,1,1,1,1 ; Initializing filter array, ARR_BUF
HX_BUF DS 	8
		
	org	p:

	global	Fmain
	
	
	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain
	;SUBROUTINE "Fasmsum",Fasmsum,FasmsumEND-Fasmsum
	
; assembly level entry point
Fmain:
	
		
		
		
		MOVEU.W  #HX_BUF, R4 ; Move array pointer of X_BUF to Register 4 
		MOVEU.W	 #Y_BUF, R5  ; Move  array pointer of Y_BUF to Register 2
		MOVE.W	#LENGTH,Y0   ; Move the Size (Length=8) to Y0

		
		MOVEU.W  #ARR_BUF, R2 ; Move  array pointer of ARR_BUF to Register 2
		
		JSR Fasmcircflip     ; Perform Circular shift on ARR_BUF by Jumping to Fasmcircshift routine
							 	
		
		DO #LENGTH,OUTER_LOOP  ; Perform a Loop for all the below functions for 'Length' times (8)
							 
		
		MOVEU.W  #X_BUF, R3  ; Move  array pointer of X_BUF to Register 3	
		
		MOVEU.W	#ARR_BUF,R2  
							 			
		
		MOVE.W	#LENGTH,Y0
		MOVEU.W	#HX_BUF, R4
		JSR Fasmmultiply     ; Perform array dot product multiplication of every value by Jumping to Fasmmultiply routine 
			
		MOVE.W	#LENGTH,Y0
		MOVEU.W	#ARR_BUF,R2		
		JSR Fasmcircshift    ; Perform Circular shift on ARR_BUF by Jumping to Fasmcircshift routine 
		
		MOVEU.W  #HX_BUF, R2
		MOVE.W	#LENGTH,Y0
		JSR Fasmsum    ; Perform Circular shift by Jumping to Fasmsum routine       
		
		MOVE.W Y0,X:(R5)+ ; Moving the final circular convolved result from the Y0 registerto internal register R5, and increment R5 each time to hold each of the values
		  

OUTER_LOOP:
		
;			
		rts
FmainEND:


Fasmcircflip:
	
	DEC.W 	Y0
	MOVE.W	Y0, R1
	ADDA	R2,R1
	ADDA	#1,	R2
SWAP_LOOP:
	CMPA	R2,R1
	BLE		DONEM
	MOVE.W	X:(R2),X0
	MOVE.W	X:(R1),Y0
	MOVE.W  X0,X:(R1)-
	MOVE.W	Y0,X:(R2)+
	BRA		SWAP_LOOP
DONEM:

	
	rts
FasmcircflipEND


Fasmmultiply:

		DO	Y0,END_LOOP
		MOVE.W	X:(R2)+,C1
		MOVE.W 	X:(R3)+,Y1	
		IMPY.W 	C1,Y1,A
		MOVE.W	A1, X:(R4)+
END_LOOP:

		RTS
		
FasmmultiplyEND:

Fasmsum:
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
FasmsumEND:

Fasmcircshift:

	DEC.W	Y0
	MOVE.W	Y0,R3
	ADDA	R3, R2
	MOVE.W	X:(R2), X0
	ADDA	#-1,R2,R1

	DO	Y0,End_Shift
	MOVE.W	X:(R1)-,C1
	MOVE.W	C1,X:(R2)-
	

End_Shift:


	MOVE.W	X0, X:(R2)

	RTS



FasmcircshiftEND:



	endsec	
	end





