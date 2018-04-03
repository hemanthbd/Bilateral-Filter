



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
		Org X:    
ARR1 	DC 		4096,4096,16384 ;Declare Arr1 
ARR2 	DC 		8192,4096,4096 	;Declare Arr2  
		Org P:  				;switch to program memory  
		MOVEU.W #ARR1,R0 		;get pointer to ARR1  
		MOVEU.W #ARR2,R3 		;get pointer to ARR2  
		CLR 	A 				;clear Accumulator A  
		MOVE.W	X:(R0)+,Y0 		;read first element of ARR1 into Y0  
		MOVE.W	X:(R3)+,X0 		;read first element of ARR2 into X0  
		REP 	#3 				;repeat next instruction 3 times  
		MAC 	Y0,X0,A X:(R0)+,Y0 X:(R3)+,X0   ;Multiply Y0*X0 + A -> A, in   
												;parallel store content of memory   
												;pointed by R0 and R3 into Y0 and X0 respectively and post increment the two pointers
		rts
FmainEND:

	endsec	

	end
