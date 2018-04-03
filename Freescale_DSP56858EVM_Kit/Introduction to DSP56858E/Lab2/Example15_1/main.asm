



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
			ORG X:
TEST_VAR	DC		5
			ORG P:	
			MOVE.W 	#3,X0			;Move 3 to X0 
			MOVEU.W #TEST_VAR, R0	;Get memory address into R0 
			SUB.W	X:(R0),X0		;Subtract 3 from TEST_VAR 
			BEQ		Increment		;If the results is zero goto 'Increment' 
			BRA		Cont_code		;Empty Else, skip to label 'Cont_code' 
Increment:	INC.W	X:(R0)			;Increment variable TEST_VAR 
Cont_code:  nop     
  			rts
FmainEND:

	endsec	

	end
