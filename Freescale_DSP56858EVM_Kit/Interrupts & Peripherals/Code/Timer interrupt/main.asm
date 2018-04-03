; interrupt registers
ITCN_BASE EQU ($1fff20)
IPR2 EQU (ITCN_BASE+$2)
IPR6 EQU (ITCN_BASE+$6)

; timer registers
TMR_BASE EQU $1ffe80
TMR0_CMP2 EQU (TMR_BASE+$1)
TMR0_LOAD EQU (TMR_BASE+$3)
TMR0_CNTR EQU (TMR_BASE+$5)
TMR0_CTRL EQU (TMR_BASE+$6)
TMR0_SCR EQU (TMR_BASE+$7)

; GPIO registers
GPIO_BASE EQU ($1ffe60)
GPIO_D_PER EQU (GPIO_BASE+$c)
GPIO_D_DDR EQU (GPIO_BASE+$d)
GPIO_D_DR EQU (GPIO_BASE+$e)

VALUE DC 0

	section rtlib
	org p:
	global Fmain
	global Ftimer_int
	SUBROUTINE "Fmain",Fmain,FmainEND-Fmain
	
Fmain:
	jsr FinitLED
	jsr FinitIsr
loop:
	nop ; do nothing
	jmp loop
	rts
FmainEND:

;Subroutine that intializes the ISR
FinitIsr:
	bfclr #$0300,sr ; allow lowest priority
	bfset #$0fc0,X:IPR6 ; interrupt for timer 0 = priority level 2
	;stop timer 0
	move.w #$0000,X:TMR0_CTRL
	; Initializing timer 0 compare 2, load
	move.w #$0000,X:TMR0_CMP2 ; comparator 2 equals $0000
	move.w #$ffff,X:TMR0_LOAD ; initial value to be loaded-65535
	; enable timer0 interrupt;
	move.w #$4000,X:TMR0_SCR ;
	; timer0 primary count source: Setting prescaler to IPBUS_CLK/32 
	move.w #$3A30,X:TMR0_CTRL ; For Period=4.194 seconds
	rts
FinitIsr_end:

;Timer ISR
Ftimer_int:
	; toggle the LEDs state
	move.w X:VALUE,A1 ; Recall the number stored in memory location VALUE
	move.w #$3f,C1 ; 6 bit mask to toggle the Least Significant 6 bits
	EOR.W C,A ; Exclusive OR current value with Mask.
	move.w A1,X:GPIO_D_DR ; 
	move.w A1, X:VALUE ; Store new number in memory location VALUE
	move.w #$4000,X:TMR0_SCR ; clear TCF bit in TMR_SCR
	rti
Ftimer_int_end:

FinitLED:
	; disable SSI peripheral
	bfclr #$003f,X:GPIO_D_PER ;
	; output direction
	bfset #$003f,X:GPIO_D_DDR ;
	; off at first
	bfclr #$003f,X:GPIO_D_DR ;
	rts
FinitLED_end:

	endsec
	end