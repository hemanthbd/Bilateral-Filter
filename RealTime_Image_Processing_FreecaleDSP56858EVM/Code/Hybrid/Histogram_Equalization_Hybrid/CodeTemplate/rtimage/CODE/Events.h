/** ###################################################################
**     Filename  : Events.H
**     Project   : rtimage
**     Processor : 56858
**     Beantype  : Events
**     Version   : Driver 01.03
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 3/8/2007, 8:50 PM
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         serial_OnError     - void serial_OnError(void);
**         serial_OnRxChar    - void serial_OnRxChar(void);
**         serial_OnTxChar    - void serial_OnTxChar(void);
**         serial_OnFullRxBuf - void serial_OnFullRxBuf(void);
**         serial_OnFreeTxBuf - void serial_OnFreeTxBuf(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2006
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "serial.h"

void serial_OnError(void);
/*
** ===================================================================
**     Event       :  serial_OnError (module Events)
**
**     From bean   :  serial [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be
**         read using <GetError> method.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void serial_OnRxChar(void);
/*
** ===================================================================
**     Event       :  serial_OnRxChar (module Events)
**
**     From bean   :  serial [AsynchroSerial]
**     Description :
**         This event is called after a correct character is
**         received. 
**         DMA mode:
**         If DMA controller is available on the selected CPU and
**         the receiver is configured to use DMA controller then
**         this event is disabled. Only OnFullRxBuf method can be
**         used in DMA mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void serial_OnTxChar(void);
/*
** ===================================================================
**     Event       :  serial_OnTxChar (module Events)
**
**     From bean   :  serial [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void serial_OnFullRxBuf(void);
/*
** ===================================================================
**     Event       :  serial_OnFullRxBuf (module Events)
**
**     From bean   :  serial [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void serial_OnFreeTxBuf(void);
/*
** ===================================================================
**     Event       :  serial_OnFreeTxBuf (module Events)
**
**     From bean   :  serial [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.79]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
