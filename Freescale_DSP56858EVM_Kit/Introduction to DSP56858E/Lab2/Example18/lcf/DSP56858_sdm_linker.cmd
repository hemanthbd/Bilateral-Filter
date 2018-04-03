


# ----------------------------------------------------

# Metrowerks sample code

# linker command file for DSP56858 EVM
#    Small Data Model (SDM)
#    boot mode 0

# ----------------------------------------------------


# see end of file for additional notes & revision history
# see Motorola docs for specific EVM memory map




# CodeWarrior preference settings:
#
#   M56800E Processor:
#     Small Program Model: OFF
#        Large Data Model: OFF
#
#   M56800E Assembler:
#        Default Data Memory Model: 16-bit
#     Default Program Memory Model: 19-bit
#
#   M56800E Target:
#     config file: 56858_ext_xp.cfg
#  
#



# 56858 memory map for SDM and 5685x boot mode 0
# x memory above 7FFF not available with SDM
# see below for memory notes


MEMORY 
{
    .p_interrupts_RAM     (RWX) : ORIGIN = 0x0,      LENGTH = 0x0100     # reserved for interrupts
    .p_RAM                (RWX) : ORIGIN = 0x0100,   LENGTH = 0x1EFF00   # contiguious int/ext pRAM combination
#   .p_internal_RAM       (RWX) : ORIGIN = 0x0100,   LENGTH = 0x9F00      
#   .p_external_RAM       (RWX) : ORIGIN = 0xA000,   LENGTH = 0x1E6000   
    .p_ROM                (RX)  : ORIGIN = 0x1F0000, LENGTH = 0x400          
#   .p_reserved                 : ORIGIN = 0x1F0400, LENGTH = 0xFBFF     
    .x_RAM                (RW)  : ORIGIN = 0x0001,   LENGTH = 0x7FFE     # contiguious int/ext xRAM with SDM limit
#   .x_internal_RAM       (RW)  : ORIGIN = 0x0001,   LENGTH = 0x0FFF     
#   .x_external_RAM_1     (RW)  : ORIGIN = 0x6000,   LENGTH = 0x1FFF     # 0x007FFF SDM limit
}




# we ensure the interrupt vector section is not deadstripped here
# the label "interrupt_vectors" comes from the vector asm file

KEEP_SECTION{ interrupt_vectors.text }



SECTIONS 
{
    .interrupt_code :
    {
        * (interrupt_vectors.text) 
       
    } > .p_interrupts_RAM
    
    
    
    .application_code :
    {
        # .text sections
        
        * (startup.text)
        * (utility.text)
        * (rtlib.text)
        * (fp_engine.text)
        * (.text)
        * (user.text)  
          
    } > .p_RAM



    .data :
    {    
        # .data sections
        
        * (.const.data.char)  # used if "Emit Separate Char Data Section" enabled
        * (.data.char)        # used if "Emit Separate Char Data Section" enabled
        * (.const.data)
        * (.data)
        * (fp_state.data)
        * (rtlib.data)
        
        
        
        # .bss sections
        
        * (rtlib.bss.lo)
        * (rtlib.bss)
        
        . = ALIGN(2);
        __bss_addr = .;
        * (.bss.char)         # used if "Emit Separate Char Data Section" enabled
        * (.bss)
        __bss_end   = .;

		__bss_size = __bss_end - __bss_addr;



        # setup the heap address 
        
        . = ALIGN(4);
        __heap_addr = .;
        __heap_size = 0x100;
        __heap_end  = __heap_addr + __heap_size; 
        . = __heap_end;



        # setup the stack address 
        
        _min_stack_size = 0x200;
        _stack_addr = __heap_end + 2;
        _stack_end  = _stack_addr + _min_stack_size;
        . = _stack_end;
        
        
        
        # used by MSL 
            
        F_heap_addr   = __heap_addr;
        F_heap_end    = __heap_end;
        
     
        
	# stationery init code uses these globals:

        F_Lstack_addr   = _stack_addr;
        
        
		# next not used in this LCF 
		# we define anyway so init code will link 
		# these can be removed with removal of rom-to-ram
		# copy code in init file
	
		F_Ldata_size     = 0x0000;
		F_Ldata_RAM_addr = 0x0000;
		F_Ldata_ROM_addr = 0x0000;		
        F_xROM_to_xRAM   = 0x0000; 
        F_pROM_to_xRAM   = 0x0000; 
        
               
	 	# zeroBSS utility
        F_Lbss_addr   = __bss_addr;
        F_Lbss_size   = __bss_size;

    } > .x_RAM    
}





# -------------------------------------------------------
# additional notes:


# about the reserved sections:

# p_interrupts_RAM -- reserved in internal pRAM
# memory space reserved for interrupt vectors
# we place interrupts 0x0000-0x0100 convention
# 5685x interrupt vectors can be elsewhere
# the vector base address register (VBA) has the vector start address
# we set the VBA in the startup code




# about the memory map:

# SDM xRAM limit is 0x7FFF

# internal and external RAM is contiguous for 5685x
# we show this with p_RAM and x_RAM





# about LCF conventions:

# program memory (p memory)
# (RWX) read/write/execute for pRAM
# (RX) read/execute for flashed pROM

# data memory (X memory)
# (RW) read/write for xRAM
# (R)  read for data flashed xROM or reserved x memory

# LENGTH = next start address - previous
# LENGTH = 0x0000 means use all remaing memory



# revision history

# 011226 R1.0  c.m. first version
# 020220 R1.1  a.h. updates
# 020308 R1.1  a.h. 56838E
# 021101 R2.0  a.h. R2.0 prep
# 021204 R2.01 a.h. bss align by 1
# 030224 R2.1  a.h. more comments
# 030731 R6.0  a.h. '53-57; updated comments




