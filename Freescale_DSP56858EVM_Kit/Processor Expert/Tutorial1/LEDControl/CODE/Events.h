/** ###################################################################
**     Filename  : Events.H
**     Project   : LEDControl
**     Processor : 56858
**     Component : Events
**     Version   : Driver 01.03
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2/16/2018, 12:17 PM
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         Time_Green_Led_OnInterrupt - void Time_Green_Led_OnInterrupt(void);
**         Button_OnInterrupt         - void Button_OnInterrupt(void);
**
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "RedLed.h"
#include "GreenLed.h"
#include "Button.h"
#include "Time_Green_Led.h"
#include "Bit1.h"
#include "EInt1.h"

void Time_Green_Led_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  Time_Green_Led_OnInterrupt (module Events)
**
**     Component   :  Time_Green_Led [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Button_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  Button_OnInterrupt (module Events)
**
**     Component   :  Button [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void EInt1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  EInt1_OnInterrupt (module Events)
**
**     Component   :  EInt1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
