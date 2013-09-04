/*
 * ks0713_Config.h - User specific configuration for Arduino GLCD library
 *
 * vi:ts=4
 *
 * Use this file to set io pins and LCD panel parameters for the KS0713 Module
 *
 * The following ks0713 pins must be straped in order to use this configuration:
 *	PS	- Strap to Vcc (indicates parallel mode)
 *	MI	- Strap to Vcc (indicates Motorola mode)
 *
 * Note: with 1 chip there is not really a need for chip select, so strap them
 * 	 to save AVR pins.
 *
 *	CS1B	- Strap to Gnd
 *	CS2		- Strap to Vcc
 */

/****************************************************************************************
 * Experimental file - this file has not been tested and is provided to support testing
 * KS0713 is not officially supported in this version of the library
 *******************************************************************************************/
 
#ifndef	GLCD_PANEL_CONFIG_H
#define GLCD_PANEL_CONFIG_H

/*
 * define name for configuration
 */
#define glcd_ConfigFile "Generic-ks0713"

/*********************************************************/
/*  Configuration for LCD panel specific configuration   */
/*********************************************************/
#define DISPLAY_WIDTH 132
#define DISPLAY_HEIGHT 65

// panel controller chips
#define CHIP_WIDTH     132	// pixels per chip 
#define CHIP_HEIGHT    65	// pixels per chip 

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/

#define glcdPinData0	PIN_B5
#define glcdPinData1	PIN_B4
#define glcdPinData2	PIN_B3
#define glcdPinData3	PIN_B2
#define glcdPinData4	PIN_B1
#define glcdPinData5	PIN_B0
#define glcdPinData6	PIN_D7
#define glcdPinData7	PIN_D6

#define glcdPinRW		PIN_D5	// RW_WR line

#define glcdPinEN		PIN_D4	// E_RD line

#define glcdPinDI		PIN_D3	// RS line



// defines for panel specific timing 
#define GLCD_tDDR	320	/* Data Delay time (E high to valid read data) 		*/
#define GLCD_tAS	140	/* Address setup time (ctrl line changes to E high)	*/
#define GLCD_tDSW	200	/* Data setup time (data lines setup to dropping E)	*/
#define GLCD_tWH    450	/* E hi level width (minimum E hi pulse width)		*/
#define GLCD_tWL	450	/* E lo level width (minimum E lo pulse width)		*/

#include "device/ks0713_Device.h"
#endif //GLCD_PANEL_CONFIG_H
