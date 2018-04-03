



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
	MOVE.W #5000, A	;store 5000 in Accumulator A 
	MOVE.W #25, Y0	;store 25 in Y0 
	IMPY.L A1,Y0,B	;16 x 16 multiply and store 31 bit result in Accumulator B
	rts
FmainEND:

	endsec	

	end
