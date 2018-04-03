



; metrowerks sample code



; NOTE: some not supported for 56855 -- see Motorola docs



; some examples of interrupts
; add and replace with your code


	section rtlib
	org	p:
	
dsp5685x_intRoutine:
	debughlt
	nop
	nop
	rti

dsp5685x_illegal:
	debughlt	; illegal instruction interrupt ($04)
	nop
	nop
	rti
	
	
dsp5685x_HWSOverflow:
	debughlt	; hardware stack overflow interrupt ($08)
	nop
	nop
	rti
	
	
dsp5685x_misalign:
	debughlt	; misaligned long word access interrupt ($0A)
	nop
	nop
	rti
	

dsp5685x_PLL:
	debughlt	; PLL lost of lock interrupt ($28)
	nop
	nop 
	rti
	
    endsec



; -----------------------------------------------------
; DSP56853-58 vector table notes

; for 56853-58, the vector base address is stored 
; in the VBA reg at ITCN_BASE + 0x09
; this defaults to zero

; we set VBA reg at startup to the vector address
; therefore, you can place the vector table anywhere via the LCF

; see dspdsp5685xum.pdf


; The reset vector for the DSPdsp5685x series devices is 0x1F0000, 
; the start address of the internal Boot ROM.
; COP reset is same.

    
    
	section interrupt_vectors
	org	p:
	
	global	Fdsp5685x_intVec


Fdsp5685x_intVec:

	jsr >dsp5685x_intRoutine    ; reserved                                ($00)
	jsr >dsp5685x_intRoutine    ; reserved                                ($02)
	jsr >dsp5685x_illegal       ; illegal instruction                     ($04)
	jsr >dsp5685x_intRoutine    ; software interrupt 3                    ($06)
	jsr >dsp5685x_HWSOverflow   ; hardware stack overflow                 ($08)
	jsr >dsp5685x_misalign      ; misaligned long word access             ($0A)
	jsr >dsp5685x_intRoutine    ; EOnCE step counter                      ($0C)
	jsr >dsp5685x_intRoutine    ; EOnCE breakpoint unit 0                 ($0E)
	jsr >dsp5685x_intRoutine    ; EOnCE breakpoint unit 1                 ($10)
	jsr >dsp5685x_intRoutine    ; EOnCE trace buffer                      ($12)
	jsr >dsp5685x_intRoutine    ; EOnCE transmit register empty           ($14)
	jsr >dsp5685x_intRoutine    ; EOnCE receive register full             ($16)
	jsr >dsp5685x_intRoutine    ; reserved                                ($18)
	jsr >dsp5685x_intRoutine    ; reserved                                ($1A)
	jsr >dsp5685x_intRoutine    ; software interrupt 2                    ($1C)
	jsr >dsp5685x_intRoutine    ; software interrupt 1                    ($1E)
	jsr >dsp5685x_intRoutine    ; software interrupt 0                    ($20)
	jsr >dsp5685x_intRoutine    ; IRQA                                    ($22)
	jsr >dsp5685x_intRoutine    ; IRQB                                    ($24)
	jsr >dsp5685x_intRoutine    ; reserved                                ($26)
	jsr >dsp5685x_PLL           ; PLL loss of lock                        ($28)
	jsr >dsp5685x_intRoutine    ; reserved                                ($2A)
	jsr >dsp5685x_intRoutine    ; dma_done0                               ($2C)
	jsr >dsp5685x_intRoutine    ; dma_done1                               ($2E)
	jsr >dsp5685x_intRoutine    ; dma_done2                               ($30)
	jsr >dsp5685x_intRoutine    ; dma_done3                               ($32)
	jsr >dsp5685x_intRoutine    ; dma_done4                               ($34)
	jsr >dsp5685x_intRoutine    ; dma_done5                               ($36)
	jsr >dsp5685x_intRoutine    ; ESSI 0 receive data /w exp status       ($38)
	jsr >dsp5685x_intRoutine    ; ESSI 0 receive data                     ($3A)
	jsr >dsp5685x_intRoutine    ; ESSI 0 receive last slot                ($3C)
	jsr >dsp5685x_intRoutine    ; ESSI 0 transmit data /w exp status      ($3E)
	jsr >dsp5685x_intRoutine    ; ESSI 0 transmit data                    ($40)
	jsr >dsp5685x_intRoutine    ; ESSI 1 receive data /w exp status       ($42)
	jsr >dsp5685x_intRoutine    ; ESSI 1 receive data                     ($44)
	jsr >dsp5685x_intRoutine    ; ESSI 1 receive last slot                ($46)
	jsr >dsp5685x_intRoutine    ; ESSI 1 receive last slot                ($48)
	jsr >dsp5685x_intRoutine    ; ESSI 1 transmit data                    ($4a)
	jsr >dsp5685x_intRoutine    ; ESSI 1 receive                          ($4c)
	jsr >dsp5685x_intRoutine    ; ESSI 1 transmit last slot               ($4e)
	jsr >dsp5685x_intRoutine    ; SPI receiver full                       ($50)
	jsr >dsp5685x_intRoutine    ; SPI transmitter empty                   ($52)
	jsr >dsp5685x_intRoutine    ; SCI transmitter empty                   ($54)
	jsr >dsp5685x_intRoutine    ; SCI transmitter idle                    ($56)
	jsr >dsp5685x_intRoutine    ; SCI receiver idle                       ($58)
	jsr >dsp5685x_intRoutine    ; SCI receiver error                      ($5a)
	jsr >dsp5685x_intRoutine    ; SCI receiver full                       ($5c)
	jsr >dsp5685x_intRoutine    ; host receive data                       ($5e)
	jsr >dsp5685x_intRoutine    ; host transmit data                      ($60)
	jsr >dsp5685x_intRoutine    ; host command (default)                  ($62)
	jsr >dsp5685x_intRoutine    ; tod alarm                               ($64)
	jsr >dsp5685x_intRoutine    ; tod one second interval                 ($66)
	jsr >dsp5685x_intRoutine    ; timer compare 0                         ($68)
	jsr >dsp5685x_intRoutine    ; timer overflow 0                        ($6a)
	jsr >dsp5685x_intRoutine    ; timer input edge flag 0                 ($6c)
	jsr >dsp5685x_intRoutine    ; timer compare 1                         ($6e)
	jsr >dsp5685x_intRoutine    ; timer overflow 1                        ($70)
	jsr >dsp5685x_intRoutine    ; timer input edge flag 1                 ($72)
	jsr >dsp5685x_intRoutine    ; timer compare 2                         ($74)
	jsr >dsp5685x_intRoutine    ; timer overflow 2                        ($76)
	jsr >dsp5685x_intRoutine    ; timer input edge flag 0                 ($78)
	jsr >dsp5685x_intRoutine    ; timer compare 0                         ($7a)
	jsr >dsp5685x_intRoutine    ; timer overflow 0                        ($7c)
	jsr >dsp5685x_intRoutine    ; timer input edge flag 0                 ($7e)
	jsr >dsp5685x_intRoutine    ; software interrupt LP                   ($80)
	jsr >dsp5685x_intRoutine    ; available for host command              ($82)
	jsr >dsp5685x_intRoutine    ; available for host command              ($FE)
	jsr >dsp5685x_intRoutine    ; available for host command              ($86)
	jsr >dsp5685x_intRoutine    ; available for host command              ($88)
	jsr >dsp5685x_intRoutine    ; available for host command              ($8A)
	jsr >dsp5685x_intRoutine    ; available for host command              ($8C)
	jsr >dsp5685x_intRoutine    ; available for host command              ($8E)
	jsr >dsp5685x_intRoutine    ; available for host command              ($90)
	jsr >dsp5685x_intRoutine    ; available for host command              ($92)
	jsr >dsp5685x_intRoutine    ; available for host command              ($94)
	jsr >dsp5685x_intRoutine    ; available for host command              ($96)
	jsr >dsp5685x_intRoutine    ; available for host command              ($98)
	jsr >dsp5685x_intRoutine    ; available for host command              ($9A)
	jsr >dsp5685x_intRoutine    ; available for host command              ($9C)
	jsr >dsp5685x_intRoutine    ; available for host command              ($9E)
	jsr >dsp5685x_intRoutine    ; available for host command              ($A0)
	jsr >dsp5685x_intRoutine    ; available for host command              ($A2)
	jsr >dsp5685x_intRoutine    ; available for host command              ($A4)
	jsr >dsp5685x_intRoutine    ; available for host command              ($A6)
	jsr >dsp5685x_intRoutine    ; available for host command              ($A8)
	jsr >dsp5685x_intRoutine    ; available for host command              ($AA)
	jsr >dsp5685x_intRoutine    ; available for host command              ($AC)
	jsr >dsp5685x_intRoutine    ; available for host command              ($AE)
	jsr >dsp5685x_intRoutine    ; available for host command              ($B0)
	jsr >dsp5685x_intRoutine    ; available for host command              ($B2)
	jsr >dsp5685x_intRoutine    ; available for host command              ($B4)
	jsr >dsp5685x_intRoutine    ; available for host command              ($B6)
	jsr >dsp5685x_intRoutine    ; available for host command              ($B8)
	jsr >dsp5685x_intRoutine    ; available for host command              ($BA)
	jsr >dsp5685x_intRoutine    ; available for host command              ($BC)
	jsr >dsp5685x_intRoutine    ; available for host command              ($BE)
	jsr >dsp5685x_intRoutine    ; available for host command              ($C0)
	jsr >dsp5685x_intRoutine    ; available for host command              ($C2)
	jsr >dsp5685x_intRoutine    ; available for host command              ($C4)
	jsr >dsp5685x_intRoutine    ; available for host command              ($C6)
	jsr >dsp5685x_intRoutine    ; available for host command              ($C8)
	jsr >dsp5685x_intRoutine    ; available for host command              ($CA)
	jsr >dsp5685x_intRoutine    ; available for host command              ($CC)
	jsr >dsp5685x_intRoutine    ; available for host command              ($CE)
	jsr >dsp5685x_intRoutine    ; available for host command              ($D0)
	jsr >dsp5685x_intRoutine    ; available for host command              ($D2)
	jsr >dsp5685x_intRoutine    ; available for host command              ($D4)
	jsr >dsp5685x_intRoutine    ; available for host command              ($D6)
	jsr >dsp5685x_intRoutine    ; available for host command              ($D8)
	jsr >dsp5685x_intRoutine    ; available for host command              ($DA)
	jsr >dsp5685x_intRoutine    ; available for host command              ($DC)
	jsr >dsp5685x_intRoutine    ; available for host command              ($DE)
	jsr >dsp5685x_intRoutine    ; available for host command              ($E0)
	jsr >dsp5685x_intRoutine    ; available for host command              ($E2)
	jsr >dsp5685x_intRoutine    ; available for host command              ($E4)
	jsr >dsp5685x_intRoutine    ; available for host command              ($E6)
	jsr >dsp5685x_intRoutine    ; available for host command              ($E8)
	jsr >dsp5685x_intRoutine    ; available for host command              ($EA)
	jsr >dsp5685x_intRoutine    ; available for host command              ($EC)
	jsr >dsp5685x_intRoutine    ; available for host command              ($EE)
	jsr >dsp5685x_intRoutine    ; available for host command              ($F0)
	jsr >dsp5685x_intRoutine    ; available for host command              ($F2)
	jsr >dsp5685x_intRoutine    ; available for host command              ($F4)
	jsr >dsp5685x_intRoutine    ; available for host command              ($F6)
	jsr >dsp5685x_intRoutine    ; available for host command              ($F8)
	jsr >dsp5685x_intRoutine    ; available for host command              ($FA)
	jsr >dsp5685x_intRoutine    ; available for host command              ($FC)
	jsr >dsp5685x_intRoutine    ; available for host command              ($FE)
	endsec	

	
	
	end




