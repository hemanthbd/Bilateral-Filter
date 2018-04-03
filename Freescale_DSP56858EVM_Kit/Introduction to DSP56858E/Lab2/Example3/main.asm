



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
	MOVE.W #10, A 		;load accumulator A with 16-bit decimal 10 
	MOVE.W #%1010, B	;load accumulator B with 16-bit binary 0000000000001010 
	MOVE.L #$A, C		;load accumulator C with 32-bit ;hexadecimal $0000000A
	rts
FmainEND:

	endsec	

	end
