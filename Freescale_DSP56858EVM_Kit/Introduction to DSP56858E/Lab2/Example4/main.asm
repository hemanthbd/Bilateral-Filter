



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
	MOVE.W #-10, A ;load accumulator A with decimal 10 or $FFF6 in two’s complement notation with sign extension 
	MOVEU.W A1, R1 ;load register R1, located in Address generation unit, with hexadecimal $FFF6 with zero extension 
	rts
FmainEND:

	endsec	

	end
