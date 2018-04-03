; GPIO registers
GPIO_BASE EQU ($1ffe60)
GPIO_D_PER EQU (GPIO_BASE+$C)
GPIO_D_DDR EQU (GPIO_BASE+$D)
GPIO_D_DR EQU (GPIO_BASE+$E)
; Interrupt Regsiters
ITCN_BASE EQU ($1fff20)
IPR2 EQU (ITCN_BASE+$2)
	section rtlib
	org p:
	global Fmain
	global FIRQA_ISR
	global FIRQB_ISR
	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain
Fmain:
	jsr FinitLED
	jsr FinitIsr
inf_loop:
	nop
	jmp inf_loop
	rts
FmainEND:
FinitLED:
	; disable SSI peripheral
	bfclr #$003f,X:GPIO_D_PER ;
	; output direction
	bfset #$003f,X:GPIO_D_DDR ;
	; off at first
	bfclr #$003f,X:GPIO_D_DR ;
	rts
FinitLED_end:
FIRQA_ISR:
	move.w #$0024,X:GPIO_D_DR ; turn green LEDs on and others off
	rti
FIRQA_ISR_end:
FIRQB_ISR:
	move.w #$0012,X:GPIO_D_DR ; turn orange LEDs on and others off
	rti
FIRQB_ISR_end:
FinitIsr:
	bfclr #$0300, sr ; allow lowest priority
	bfset #$000a, X:IPR2 ;Setting priority level 2 for IRQA/IRQB in IPR2
	rts
FinitIsr_end
	endsec
	end