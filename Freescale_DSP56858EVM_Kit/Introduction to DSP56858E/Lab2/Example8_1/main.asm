



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
		ORG X:   
X1		DCB		2,3,4,5   
		ORG P:    
		MOVE.L	#@lb(X1), R1	;move lower-bit of word pointer to R1  
		MOVE.W 	#0, A			;clear A  
		MOVE.W 	#0, B 			;clear B  
		DO 		#4,Loop			;start looping  
		MOVE.BP X:(R1+0),B		;read every byte pointer and store in B  
		ADD 	B, A 			;Add A + B -> A  
		ADDA 	#1, R1			;increment R1 
Loop:     
		rts

FmainEND:

	endsec	

	end
