



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
	MOVE.W #5, A	;store 5 in Accumulator A    
	MOVE.W #5, Y0	;store 5 in Y0 
	MPY A1,Y0,B		;16 x 16 fractional multiply 
	MOVE.W B, X0	;MOVE B1 to X0 
	rts
FmainEND:

	endsec	

	end
