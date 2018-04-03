



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
	MOVE.W #16384, A	;store 16384(0.5 in Q15) in Accumulator A    
	MOVE.W #16384, Y0	;store 16384(0.5 in Q15) in Y0 
	MPY A1,Y0,B			;16 x 16 fractional multiply 
	MOVE.W B, X0		;MOVE B1 to X0 
	rts
FmainEND:

	endsec	

	end
