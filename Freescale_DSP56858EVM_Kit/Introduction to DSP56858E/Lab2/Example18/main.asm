



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
			MOVEU.W #TEST_VAR,R0	;Get memory address 
Loop:    
			REP 	#10				;Repeat the following instruction 10 times 
			INC.W 	X:(R0) 			;Increment the value of TEST_VAR by 1
  			rts
FmainEND:

	endsec	

	end
