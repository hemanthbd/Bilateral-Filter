



; metrowerks sample code



	section rtlib
	org	p:

	global	Fmain

	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain

; assembly level entry point
Fmain:
	MOVE.W #$FF0A, X:$0000	;load data memory $0000 with $FF0A 
	MOVE.W #$FF0B, X:$0001	;load data memory $0001 with $FF0B 
	MOVE.L #$0000, R0 		;store $0000 into R0   
	MOVE.W X:(R0)+, X0		;read data memory $0000 to internal register X0 and increment R0 by one 
	MOVE.W X:(R0), Y0		;read data memory $0001 and store result in Y0   
	MOVE.W X:(R0+2), Y0		;read data memory $0001 + 2 = $0003 and store result in Y0 
	MOVE.W #10, N			;Store 10 into register N 
	MOVE.W X:(R0+N), A		;read data memory $0001 + N =$000B and store result in A 
	MOVE.W X:(R0)+N, B		;read data memory $0001 and store result in B, increment R0 by N 
	MOVE.W X:(R0-1), C 		;read data memory $000B - 1 =$000A and store result in C 
	rts
FmainEND:

	endsec	

	end
