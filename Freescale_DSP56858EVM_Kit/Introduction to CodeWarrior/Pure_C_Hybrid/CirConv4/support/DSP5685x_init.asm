



; metrowerks sample code



; OMR mode bits

NL_MODE EQU $8000
CM_MODE EQU	$0100
XP_MODE EQU	$0080
R_MODE  EQU	$0020
SA_MODE EQU	$0010


; vector base address register

ITCN_BASE EQU $1FFF20  
VBA_reg   EQU $1FFF29  ; ITCN_BASE + 0x09




	section		startup

	XREF	F_stack_addr
	org	p:

	
	GLOBAL Finit_dsp5685x_

	SUBROUTINE "Finit_dsp5685x_",Finit_dsp5685x_,Finit_dsp5685x_END-Finit_dsp5685x_

Finit_dsp5685x_:


; setup the OMR with the values required by C

	bfset	#NL_MODE,omr		    ; ensure NL=1  (enables nested DO loops)
	nop
	nop

                                    ; ensure CM=0  (optional for C)
                                    ; ensure XP=0 to enable harvard architecture
                                    ; ensure R=0  (required for C)
                                    ; ensure SA=0 (required for C)

	bfclr	#(CM_MODE|XP_MODE|R_MODE|SA_MODE),omr   
	
													
			
													
	move.w	#-1,x0
	moveu.w	x0,m01                  ; set the m register to linear addressing
				
	moveu.w	hws,la                  ; clear the hardware stack
	moveu.w	hws,la
	nop
	nop
	
	
	
	move.l	#>>Fdsp5685x_intVec, r1 ; set the vector base address reg
	move.w	r1, x:>>VBA_reg         ; no matter where the vectors reside via LCF
	nop                             ; they will be found with the VBA reg
	nop



CALLMAIN:                           ; initialize compiler environment
                                         
	move.l #>>F_Lstack_addr,r0      ; initialize the stack
	bftsth #$0001,r0
	bcc noinc
	adda #1,r0
noinc:
	tfra	r0,sp                   ; set stack pointer too
	move.w	#0,r1
	nop
	move.w	r1,x:(sp)
	adda	#1,sp	
	
	
 	jsr		F__zeroBSS        		; fill BSS space with zeroes



; call main()

	move.w	#0,y0                   ; pass parameters to main()
	move.w	#0,r2
	move.w	#0,r3

	jsr	 	Fmain                   ; call the users program



                                    ; end of program
                                    
                                    ; hostIO cleanup with exit_halt
    jsr     Fexit_halt              ; stationery examples use standard i/o 
                                    ; such as printf implemented with hostIO 
                                    ; so we use exit_halt here 
                                    ; see runtime file exit_dsp.asm
                                    ; comment out exit_halt if not using hostIO
                                    
                                    
    
    debughlt                        ; or simple end of program; halt CPU	
	rts 
Finit_dsp5685x_END:

	endsec
	
	
	
	
	
	
	
	
	