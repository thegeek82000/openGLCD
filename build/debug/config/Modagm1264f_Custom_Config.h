/*
 * Modagm1264f_Custom_Config.h - User specific configuration for Arduino GLCD library
 *
 * Use this file to set io pins and LCD panel parameters
 *
 *	This configuration file is for the AGM1264F module manufactured by AZ Displays.
 *	This module uses 2 ks0108 chips each controlling one half of the display.
 *
 *	This is the 128x64 GLCD that was sold by BGmicro
 *	The datasheet can be downloaded from here:
 *	http://docs.bgmicro.com/pdf/lcd1030.pdf
 *	
 *
 *
 *    <-------------------------------- 128 Pixels -------------------------------->
 *    +--------------------------------------+-------------------------------------+ 
 *    |                                      |                                     | ^
 *    |<------------ 64 Pixels ------------->|                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | 64 pixels
 *    |    Chip 0 controls these pixels      |     Chip 1 Controls these pixels    | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | v
 *    +--------------------------------------+-------------------------------------+
 *    |       |20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1|        |
 *    +----------------------------------------------------------------------------+
 *
 *    +-------------------------------------------+
 *    |Pin|Symbol|        Function                | Hook To
 *    +-------------------------------------------+
 *    | 1 | Vss  | Ground                         | Gnd
 *    +-------------------------------------------+
 *    | 2 | Vdd  | +5v (15ma max)                 | +5v ---------------------+
 *    +-------------------------------------------+                          |
 *    | 3 | Vo   | LCD contrast adjust            |--------------------+     |
 *    +-------------------------------------------+                    |     |
 *    | 4 | DI   | H = Data, L=instruction/Status | glcdPinDI          |     |
 *    +-------------------------------------------+                    |     |
 *    | 5 | RW   | H = Read, L = Write            | glcdPinRW          |     |
 *    +-------------------------------------------+                    |     |
 *    | 6 | E    | Enable signal                  | glcdPinEN          |     |
 *    +-------------------------------------------+                    |     |
 *    | 7 | DB0  | Data Bit 0                     | glcdPinData0       |     |
 *    +-------------------------------------------+                    |     |
 *    | 8 | DB1  | Data Bit 1                     | glcdPinData1       |     |
 *    +-------------------------------------------+                    |     |
 *    | 9 | DB2  | Data Bit 2                     | glcdPinData2       |     |
 *    +-------------------------------------------+                    |     |
 *    |10 | DB3  | Data Bit 3                     | glcdPinData3 /\/\/\/\/\/\|
 *    +-------------------------------------------+              |  (10-20k)
 *    |11 | DB4  | Data Bit 4                     | glcdPinData4 | 
 *    +-------------------------------------------+              | Contrast Pot
 *    |12 | DB5  | Data Bit 5                     | glcdPinData5 |
 *    +-------------------------------------------+              |
 *    |13 | DB6  | Data Bit 6                     | glcdPinData6 |
 *    +-------------------------------------------+              |
 *    |14 | DB7  | Data Bit 7                     | glcdPinData7 |
 *    +-------------------------------------------+              |
 *    |15 | CS1  | H = chip 0 selected            | glcdPinCS1   |
 *    +-------------------------------------------+              |
 *    |16 | CS2  | H = chip 1 selected            | glcdPinCS2   |
 *    +-------------------------------------------+              |
 *    |17 | RST  | L = Reset                      | AVR Pin      |
 *    +-------------------------------------------+              |
 *    |18 | VEE  | LCD contrast power supply      |--------------+
 *    +-------------------------------------------+
 *    |19 | BL-  | Backlight -/gnd                | Gnd
 *    +-------------------------------------------+
 *    |20 | BL+  | Backlight + (560ma max)        | 4-10+ ohm Resistor to +5v
 *    +-------------------------------------------+
 *
 */
#ifndef	GLCD_PANEL_CONFIG_H
#define GLCD_PANEL_CONFIG_H

/*
 * define name for configuration
 */
#define glcd_ConfigName "Custom-AGM1264F"

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

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/

/*
 * Pins can be assigned using arduino pin numbers 0-n
 * Pins can also be assigned using PIN_Pb 
 *		where P is port A-L and b is bit 0-7
 *		Example: port D pin 3 is PIN_D3
 *
 */


/* Data pin definitions
 */
#define glcdPinData0		8
#define glcdPinData1		9
#define glcdPinData2		10
#define glcdPinData3		11
#define glcdPinData4		4
#define glcdPinData5		5
#define glcdPinData6		6
#define glcdPinData7		7

/* Arduino pins used for Commands
 * default assignment uses the first five analog pins
 */
#define glcdPinCSEL1		14
#define glcdPinCSEL2		15
// uncomment the following if more than two chip select pins are needed
//#define glcdPinCSEL3		3   // third chip select line on pin 3 if needed
//#define glcdPinCSEL4		2   // fourth chip select if needed

#define glcdPinRW			16
#define glcdPinDI			17
#define glcdPinEN			18
// Reset - uncomment the next line if reset is connected to an output pin
//#define glcdPinRES	        19	// s/w Reset control

//#define glcdPinBL	        ?	// s/w backlight control

/*********************************************************/
/*  Chip Select pin assignments                          */
/*********************************************************/
#define CS_2Chips_2Pins    // default has two chips selected using two pins
//#define CS_2Chips_1Pin   // 2 chips selected using one CS pin (the other CS is inverted in hardware)
//#define CS_3Chips_2Pins  // 3 chips selected using two CS pins
//#define CS_3Chips_3Pins  // 3 chips selected using three CS pins
//#define CS_4Chips_2Pins  // 4 chips selected using two CS pins
//#define CS_4Chips_4Pins  // 4 chips selected using 4 CS pins

/*
 * Two Chip panels using two select pins
 */

#ifdef CS_2Chips_2Pins
#define glcd_CHIP0 glcdPinCSEL1,HIGH, glcdPinCSEL2,LOW
#define glcd_CHIP1 glcdPinCSEL1,LOW, glcdPinCSEL2,HIGH

/*
 * Two Chip panels using one select pin
 */
 #elif defined  CS_2Chips_1Pin
#define glcd_CHIP0 glcdPinCSEL1,LOW
#define glcd_CHIP1 glcdPinCSEL1,HIGH

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
 * Four Chip panel using four select pins
 *
 * Don't forget that glcdPinCSEL3 and glcdPinCSEL4 need to defined
 */
#elif defined CS_4Chips_4Pins
#define glcd_CHIP0 glcdPinCSEL1,HIGH, glcdPinCSEL2,LOW, glcdPinCSEL3, LOW, glcdPinCSEL4, LOW
#define glcd_CHIP1 glcdPinCSEL1,LOW, glcdPinCSEL2,HIGH, glcdPinCSEL3, LOW, glcdPinCSEL4, LOW
#define glcd_CHIP2 glcdPinCSEL1,LOW, glcdPinCSEL2,LOW, glcdPinCSEL3, HIGH, glcdPinCSEL4, LOW
#define glcd_CHIP3 glcdPinCSEL1,LOW, glcdPinCSEL2,LOW, glcdPinCSEL3, LOW, glcdPinCSEL4, HIGH

/*
 * Four Chip panel using two select pins
 */
#elif defined CS_4Chips_2Pins
#define glcd_CHIP0 glcdPinCSEL1,LOW, glcdPinCSEL2,LOW
#define glcd_CHIP1 glcdPinCSEL1,HIGH, glcdPinCSEL2,LOW
#define glcd_CHIP2 glcdPinCSEL1,HIGH, glcdPinCSEL2,HIGH
#define glcd_CHIP3 glcdPinCSEL1,LOW, glcdPinCSEL2,HIGH

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
