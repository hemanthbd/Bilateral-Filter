



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
			ORG X:
TEST_VAR	DC		0
			ORG P:	
			MOVEU.W	#TEST_VAR,R0	;Get memory address 
			MOVE.W	#10, A1			;Move 10 to Accumulator 
Loop:    
			INC.W 	X:(R0) 			;Increment the value of TEST_VAR by 1
  			DEC.W	A 				;Decrement Accumulator by one 
  			BNE		Loop			;Continue till A becomes 0
  			rts
FmainEND:

	endsec	

	end
