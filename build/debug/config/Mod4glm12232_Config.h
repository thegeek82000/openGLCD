/*
 * Mod4glm12232_Config.h - User specific configuration for Arduino GLCD library
 *
 * vi:ts=4
 *
 * Use this file to set io pins and LCD panel parameters for 
 *
 *	This configuration file is for the 4GLM12232 module manufactured by Falcon.
 *	This module uses 2 sed1520 chips each controlling one half of the display.
 *	The data sheet for this module is very confusing. It seems to show 2
 *	122x16 LCD panels.
 *
 *	This in fact is the case with this particular module. There are 2 122x16 LCD
 *	displays in one package. But each sed1520 chip controls 1 half of each of
 *	the two seperate displays.
 *
 *	So while it is addressed as if it were a 122x32 LCD display,
 *	because this LCD panel is really 2 seperate LCD panesl there is a gap betwen
 *	the upper half and the lower half of the display pixels. Therefore this display
 *	should not really be considered a true 122x32 display because it is not.
 *
 *	Seek a different model if a true 122x32 LCD display is desired.
 *
 *	This display also uses a flex cable instead of having true "pins" or solder holes
 *	which makes it more difficult to hook up.
 *
 *
 *    <-------------------------------- 122 Pixels -------------------------------->               
 *    +--------------------------------------+-------------------------------------+           +----+
 *    |                                      |                                  ^  | ^         |Pins|
 *    |<------------ 61 Pixels ------------->|                                  |  | |         |  1 |
 *    |                                      |                                  |  | |         |  2 |
 *    |                                      |                                  |  | |         |  3 |
 *    |                                      |                            16 Pixels| |         |  4 |
 *    |                                      |                                  |  | |         |  5 |
 *    |                                      |                                  |  | |         |  5 |
 *    |                                      |                                  |  | |         |  6 |
 *    |    Chip 0 controls these pixels      |     Chip 1 Controls these pixels v  | |         |  7 |
 *    +--------------------------------------+-------------------------------------+ |         |  8 |
 *    |                       GAP between upper an lower pixels                    | 32 pixels |  9 |
 *    +--------------------------------------+-------------------------------------+ |         | 10 |
 *    |                                      |                                  ^  | |         | 11 |
 *    |<------------ 61 Pixels ------------->|                                  |  | |         | 12 |
 *    |                                      |                                  |  | |         | 13 |
 *    |                                      |                                  |  | |         | 13 |
 *    |                                      |                            16 Pixels| |         | 14 |
 *    |                                      |                                  |  | |         | 15 |
 *    |                                      |                                  |  | |         | 16 |
 *    |                                      |                                  |  | |         | 17 |
 *    |    Chip 0 controls these pixels      |     Chip 1 Controls these pixels v  | v         | 18 |
 *    +--------------------------------------+-------------------------------------+           +----+
 *
 *    +-------------------------------------------+
 *    |Pin|Symbol|        Function                | Hook To
 *    +-------------------------------------------+
 *    | 1 | Vdd  | +5v (15ma max)                 | +5v
 *    +-------------------------------------------+
 *    | 2 | Vss  | Ground                         | Gnd
 *    +-------------------------------------------+
 *    | 3 | VLCD | LCD contrast adjust            | ???
 *    +-------------------------------------------+
 *    | 4 | RST  | L = Reset                      | +5v or glcdPinRES for s/w control
 *    +-------------------------------------------+
 *    | 5 | E1   | chip 0 enable stobe            | glcdPinE1
 *    +-------------------------------------------+
 *    | 6 | E2   | chip 1 enable strobe           | glcdPinE2
 *    +-------------------------------------------+
 *    | 7 | RW   | H = Read, L = Write            | glcdPinRW
 *    +-------------------------------------------+
 *    | 8 | A0/DI| H = Data, L=instruction/Status | glcdPinDI
 *    +-------------------------------------------+
 *    | 9 | DB0  | Data Bit 0                     | glcdPinData0
 *    +-------------------------------------------+
 *    |10 | DB1  | Data Bit 1                     | glcdPinData1
 *    +-------------------------------------------+
 *    |11 | DB2  | Data Bit 2                     | glcdPinData2
 *    +-------------------------------------------+
 *    |12 | DB3  | Data Bit 3                     | glcdPinData3
 *    +-------------------------------------------+
 *    |13 | DB4  | Data Bit 4                     | glcdPinData4
 *    +-------------------------------------------+
 *    |14 | DB5  | Data Bit 5                     | glcdPinData5
 *    +-------------------------------------------+
 *    |15 | DB6  | Data Bit 6                     | glcdPinData5
 *    +-------------------------------------------+
 *    |16 | DB7  | Data Bit 7                     | glcdPinData7
 *    +-------------------------------------------+
 *    |17 | BL-  | Backlight -/gnd                | Gnd
 *    +-------------------------------------------+
 *    |18 | BL+  | Backlight + (200ma max)        |  ???
 *    +-------------------------------------------+
 *
 */

#ifndef	GLCD_PANEL_CONFIG_H
#define GLCD_PANEL_CONFIG_H

/*
 * define name for configuration
 */
#define glcd_ConfigName	"Generic-4GLM12232"

/*********************************************************/
/*  Configuration for LCD panel specific configuration   */
/*********************************************************/
#define DISPLAY_WIDTH 122
#define DISPLAY_HEIGHT 32

// panel controller chips
#define CHIP_WIDTH     61  // pixels per chip 
#define CHIP_HEIGHT    32  // pixels per chip 

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


#define glcdPinData0	PIN_B5
#define glcdPinData1	PIN_B4
#define glcdPinData2	PIN_B3
#define glcdPinData3	PIN_B2
#define glcdPinData4	PIN_B1
#define glcdPinData5	PIN_B0
#define glcdPinData6	PIN_D7
#define glcdPinData7	PIN_D6

#define glcdPinRW		PIN_D5

#define glcdPinE1		PIN_D4

#define glcdPinDI		PIN_D3	// A0 line

#define glcdPinE2		PIN_D2


// defines for panel specific timing 
#define GLCD_tDDR	320	/* tACC6: Data Delay time (E high to valid read data) 			*/
#define GLCD_tAS	20	/* tAW6:  Address setup time (ctrl line changes to E high)		*/
#define GLCD_tDSW	200	/* tDS6:  Data setup time (Write data lines setup to dropping E)*/
#define GLCD_tWH	450	/* tEW:   E hi level width (minimum E hi pulse width)			*/ 
#define GLCD_tWL	450	/* E lo level width (minimum E lo pulse width)					*/


#include "device/sed1520_Device.h"
#endif //GLCD_PANEL_CONFIG_H
