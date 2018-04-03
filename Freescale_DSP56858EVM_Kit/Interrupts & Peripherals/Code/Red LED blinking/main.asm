;-----------------------------------------------------------------------
;Turning red LEDs ON
;-----------------------------------------------------------------------
; GPIO Registers
GPIO_BASE EQU ($1ffe60) 		;base address for port registers
GPIO_D_PER EQU (GPIO_BASE+$C)
GPIO_D_DDR EQU (GPIO_BASE+$D)
GPIO_D_DR EQU (GPIO_BASE+$E)
	section rtlib
	org p:
	global Fmain
	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain
Fmain:
	jsr FinitLED 				; initiliaze LEDs and turn them OFF
	move.w #$0009, X:GPIO_D_DR 	; turn red LEDs ON
	rts
FmainEND:

FinitLED:
	; disable ESSI peripheral by clearing the first 6 bits
	bfclr #$003f,X:GPIO_D_PER ;
	; output direction
	bfset #$003f,X:GPIO_D_DDR ;
	; off at first
	bfclr #$003f,X:GPIO_D_DR ;
	rts
FinitLED_end:
	endsec
	end