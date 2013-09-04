/*
 * glcd_Teensy_Config.h - User specific configuration for Arduino GLCD library
 *
 * vi:ts=4
 *
 * Use this file to set io pins and LCD panel parameters
 * This version is for a standard ks0108 display
 * connected to a Teesny or Teesny++
 *
 * Note that the Teensy and Teensy++ use different pin numbers 
 * so make sure that your wiring matches the device you are using
 *
*/

#ifndef	GLCD_PANEL_CONFIG_H
#define GLCD_PANEL_CONFIG_H


/*********************************************************/
/*  Configuration for LCD panel specific configuration   */
/*********************************************************/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// panel controller chips
#define CHIP_WIDTH     64  // pixels per chip
#define CHIP_HEIGHT    64  // pixels per chip

// calculate number of chips & round up if width is not evenly divisable
#define glcd_CHIP_COUNT ((DISPLAY_WIDTH + CHIP_WIDTH - 1)  / CHIP_WIDTH)

/**********************************************************/
/*  Configuration for assigning LCD bits to Teensy++ Pins */
/**********************************************************/
 
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__) // Teensy++

#define glcd_ConfigName "Teensy++ ks0108"   // define name for configuration

#define glcdPinCSEL1            PIN_E6 
#define glcdPinCSEL2            PIN_E7
#define glcdPinRW               PIN_E0
#define glcdPinDI               PIN_E1
#define glcdPinEN               PIN_D7
//#define glcdPinRES	          5	// Reset Bit 

#define glcdPinData0         PIN_C0
#define glcdPinData1         PIN_C1
#define glcdPinData2         PIN_C2
#define glcdPinData3         PIN_C3
#define glcdPinData4         PIN_C4
#define glcdPinData5         PIN_C5
#define glcdPinData6         PIN_C6
#define glcdPinData7         PIN_C7

#warning "KS0108 using pins for teensy++"

/*********************************************************/
/*  Configuration for assigning LCD bits to Teensy Pins  */
/*********************************************************/
#elif defined(__AVR_ATmega32U4__)   // Teensy 2.0

#define glcd_ConfigName "Teensy ks0108"   // define name for configuration

#define glcdPinCSEL1            PIN_D2	// normal connection for control signals
#define glcdPinCSEL2            PIN_D3
#define glcdPinRW               PIN_D1
#define glcdPinDI               PIN_D0
#define glcdPinEN               PIN_C6
//#define glcdPinRES		            17	// Reset Bit 

#define glcdPinData0            PIN_B0
#define glcdPinData1            PIN_B1
#define glcdPinData2            PIN_B2
#define glcdPinData3            PIN_B3
#define glcdPinData4            PIN_B4
#define glcdPinData5            PIN_B5
#define glcdPinData6            PIN_B6
#define glcdPinData7            PIN_B7

#warning "KS0108 using pins for teensy 2.0"
#endif

/*********************************************************/
/*  Chip Select pin assignments                          */
/*********************************************************/
#define CS_2Chips_2Pins    // default has two chips selected using two pins
//#define CS_3Chips_2Pins  // 3 chips selected using two pins
//#define CS_3Chips_3Pins  // 3 chips selected using three pins

/*
 * Two Chip panels using two select pins
 */

#ifdef CS_2Chips_2Pins
#define glcd_CHIP0 glcdPinCSEL1,HIGH, glcdPinCSEL2,LOW
#define glcd_CHIP1 glcdPinCSEL1,LOW, glcdPinCSEL2,HIGH

/*
 * Three Chip panel using two select pins
 */
#elif defined CS_3Chips_2Pins
#define glcd_CHIP0 glcdPinCSEL1,LOW, glcdPinCSEL2,HIGH
#define glcd_CHIP1 glcdPinCSEL1,HIGH, glcdPinCSEL2,LOW
#define glcd_CHIP2 glcdPinCSEL1,LOW, glcdPinCSEL2,LOW

 /*
 * example of three Chip panel using three select pins
 * in this example, the chip is selected by setting a corresponding pin LOW
 *
 * Don't forget that glcdPinCSEL3 needs to defined (uncommented in the command
pin assignments)
 */
#elif defined CS_3Chips_3Pins
#define glcd_CHIP0 glcdPinCSEL1,HIGH, glcdPinCSEL2,LOW,glcdPinCSEL3,LOW
#define glcd_CHIP1 glcdPinCSEL1,LOW, glcdPinCSEL2,HIGH,glcdPinCSEL3,LOW
#define glcd_CHIP2 glcdPinCSEL1,LOW, glcdPinCSEL2,LOW,glcdPinCSEL3,HIGH
#endif


/*
 * The following defines are for panel specific low level timing.
 *
 * See your data sheet for the exact timing and waveforms.
 * All defines below are in nanoseconds.
 */

#define GLCD_tDDR	320	/* Data Delay time (E high to valid read data) 		*/
#define GLCD_tAS	140	/* Address setup time (ctrl line changes to E high)	*/
#define GLCD_tDSW	200	/* Data setup time (data lines setup to dropping E)	*/
#define GLCD_tWH	450	/* E hi level width (minimum E hi pulse width)		*/
#define GLCD_tWL	450	/* E lo level width (minimum E lo pulse width)		*/


#include "device/ks0108_Device.h"
#endif //GLCD_PANEL_CONFIG_H
