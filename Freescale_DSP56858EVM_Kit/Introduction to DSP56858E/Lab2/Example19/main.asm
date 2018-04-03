



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
			ORG X:
TEST_VAR	DC	0
			ORG P:	
			MOVEU.W #TEST_VAR, R0	;Get memory address  
			DO #10,Loop				;Do Looping 10 times 
			INC.W X:(R0) 			;Increment variable TEST_VAR 
			MOVE.W X:(R0), X0 		;Move TEST_VAR to register X0 
			ASL.W X0 				;Multiply X0 by 2 by shifting to the left 
			MOVE.W X0, X:(R0) 		;Store the result back to TEST_VAR 
Loop:    
  			rts
FmainEND:

	endsec	

	end
