



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
		MOVE.W	#$000A, A	;load 10 into A  
		BRA		SKIP		;Branch unconditionally to label SKIP.  
		MOVE.W	#$00FF, A	;This instruction is skipped 
SKIP	MOVE.W	#$00AA, B	;Initialize accumulator B 
		rts
FmainEND:

	endsec	

	end
