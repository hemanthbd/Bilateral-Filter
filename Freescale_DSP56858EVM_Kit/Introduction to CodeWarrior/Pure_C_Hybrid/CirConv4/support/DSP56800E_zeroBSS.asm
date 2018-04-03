  
   


; metrowerks sample code



; zeroes BSS

; we use unsigned long moves for setup of start address and size
; otherwise the values will be sign-extended





	section utility
	
	XREF	F_Lbss_addr
	XREF	F_Lbss_size


	org	p:

	
	GLOBAL F__zeroBSS

	SUBROUTINE "F__zeroBSS",F__zeroBSS,F__zeroBSSEND-F__zeroBSS


F__zeroBSS:


; Stationery default routine
; 56800E LC register doesn't have 8191 element limitation of 56800
; so we can use hardware loop here



; zeroBSS hardware loop	

    move.l  #>>F_Lbss_size,r2       ; move count
    move.l  #>>F_Lbss_addr,r1       ; start address is BSS start
    move.w  #0,x0    				; zero value
    nop
    
    do      r2,>>end_zeroBSS        ; copy for r2 times
    nop
    move.w  x0,x:(r1)+              ; stash value at x address r1   
	    
end_zeroBSS:                      
	rts 

F__zeroBSSEND:

	endsec
	end
	
	
	