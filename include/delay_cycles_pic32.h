/*
 *  delay_cycles_pic32.h
 *
 * Provides accurate cycle delays for a given number of i/o clocks.
 * This version is for the pic32 and is part of the openGLCD library.
 */


#ifndef _DELAY_CYCLES_PIC32_H_
#define _DELAY_CYCLES_PIC32_H_

#include <inttypes.h>

/*
 *
 *  _delay_cycles(uint32 _IOticks)
 *
 *  Perform an accurate delay of a given number of i/o cycles.
 *  NOTE: i/o cycles are half the processor pic32 clock
 *
 *  All the floating point arithmetic will be handled by the
 *  GCC Preprocessor and no floating point code will be generated.
 *  Allthough the parameter __ticks_d is of type 'double' this
 *  function can be called with any constant integer value, too.
 *  GCC will handle the casting appropriately.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif
#include <peripheral/timer.h>
#ifdef __cplusplus
}
#endif

/*
 * plib is no longer used in newer rleases, so this checks for that
 * and makes adjustments.
 * apparently, the non plib function to read the timer is readCoreTimer() 
 */
#ifndef _PERIPHERAL_LIBRARY_MASTER_HEADER_FILE
#define ReadCoreTimer() readCoreTimer()
#endif

static __inline__ void
_delay_cycles(uint32_t _IOticks)
{
#if 1
uint32_t startTicks = ReadCoreTimer();

	while((ReadCoreTimer() - startTicks) < _IOticks)
	{
		; // do nothing, while spinning
	}
#else

	/*
	 * About the same delay as above
	 */
	_IOticks /= 2;
	while(_IOticks--)
	{
		Nop();
	}
#endif
}

#endif /* _DELAY_CYCLES_PIC32 */
