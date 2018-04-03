



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
			ORG X:
TEST_VAR	DC		3
			ORG P:	
			MOVE.W 	#3,X0			;Move 3 to X0 
			MOVEU.W #TEST_VAR, R0	;Get memory address into R0 
			SUB.W	X:(R0),X0		;Subtract 3 from TEST_VAR 
			BNE		Decrement		;If the results is zero goto 'Decrement' 
			BRA		Increment		;Else, go to label 'Increment' 
Increment:	INC.W	X:(R0)			;Increment variable TEST_VAR 
			BRA		SKIP			;If'Increment',skip the next instruction
Decrement:  DEC.W	X:(R0)   		;Decrement variable 'TEST_VAR'
SKIP  		rts
FmainEND:

	endsec	

	end
