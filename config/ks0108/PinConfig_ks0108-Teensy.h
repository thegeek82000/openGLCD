/*
 * ks0108_Teensy.h - User specific configuration for openGLCD library
 *
 * Use this file to set io pins
 * when using a Teensy, Teensy++, or Teensy3/3.1
 *
 * Note that each board uses different pin numbers 
 * so make sure that your wiring matches the device you are using
 *
 */

#ifndef GLCD_PIN_CONFIG_H
#define GLCD_PIN_CONFIG_H

/**********************************************************/
/*  Configuration for assigning LCD pins to Teensy++ Pins */
/**********************************************************/

/*
 * Pins can be assigned using Arduino pin numbers 0-n
 * Pins on AVR devices can also be assigned using PIN_Pb 
 *    where P is port A-L and b is bit 0-7
 *    Example: port D bit 3 is PIN_D3
 *
 */

 
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__) // Teensy++ 2.0

#define glcd_PinConfigName "ks0108-Teensy++"   // define name for configuration
/*
 *                Arduino pin    AVR pin
 */ 
#define glcdPinData0    10      // PIN_C0
#define glcdPinData1    11      // PIN_C1
#define glcdPinData2    12      // PIN_C2
#define glcdPinData3    13      // PIN_C3
#define glcdPinData4    14      // PIN_C4
#define glcdPinData5    15      // PIN_C5
#define glcdPinData6    16      // PIN_C6
#define glcdPinData7    17      // PIN_C7

#define glcdPinDI       9       // PIN_E1
#define glcdPinRW       8       // PIN_E0
#define glcdPinEN       7       // PIN_D7
#define glcdPinCSEL1    18      // PIN_E6 
#define glcdPinCSEL2    19      // PIN_E7

//#define glcdPinBL       27      // PIN_B7     // optional backlight control pin controls BL circuit
//#define glcdPinRES      5       // PIN_D5     // optional s/w reset control

#if NBR_CHIP_SELECT_PINS > 2
#error Missing glcdPinCSEL3 define
//#define glcdPinCSEL3    ?   // third chip select if needed
#endif

#if NBR_CHIP_SELECT_PINS > 3
#error Missing glcdPinCSEL4 define
//#define glcdPinCSEL4    ?   // fourth chip select if needed
#endif


//#warning "KS0108 using pins for teensy++"

/***********************************************************/
/*  Configuration for LCD pins to Teensy 3.0/3.1/LC        */
/***********************************************************/
#elif defined(__MK20DX128__)   || defined(__MK20DX256__) || defined(__MKL26Z64__) // Teensy 3.0/Teensy 3.1/LC

#define glcd_PinConfigName "ks0108-Teensy3"   // define name for configuration

// "default" Teensy 3.0/3.1 connections
// used on GLCD demo board for Bill Perry

#define glcdPinData0      16
#define glcdPinData1      17
#define glcdPinData2      18 // i2c SDA0
#define glcdPinData3      19 // i2c SCL0
#define glcdPinData4      20
#define glcdPinData5      21
#define glcdPinData6      22
#define glcdPinData7      23


#define glcdPinDI          9
#define glcdPinRW          8
#define glcdPinEN          7
#define glcdPinCSEL1       3
#define glcdPinCSEL2       2
#if NBR_CHIP_SELECT_PINS > 2
#error Missing glcdPinCSEL3 define
//#define glcdPinCSEL3    ?   // third chip select if needed
#endif

#if NBR_CHIP_SELECT_PINS > 3
#error Missing glcdPinCSEL4 define
//#define glcdPinCSEL4    ?   // fourth chip select if needed
#endif

//#define glcdPinBL          ?      //  optional backlight control pin controls BL circuit
//#define glcdPinRES         ?      //  optional s/w reset control

//#warning "KS0108 using pins for Teensy 3.0"

/*********************************************************/
/*  Configuration for assigning LCD pins to Teensy Pins  */
/*********************************************************/
#elif defined(__AVR_ATmega32U4__)   // Teensy 2.0

#define glcd_PinConfigName "ks0108-Teensy"   // define name for configuration

/*
 *                 Arduino pin    AVR pin
 */ 
#define glcdPinData0    0        // PIN_B0
#define glcdPinData1    1        // PIN_B1
#define glcdPinData2    2        // PIN_B2
#define glcdPinData3    3        // PIN_B3
#define glcdPinData4    13       // PIN_B4
#define glcdPinData5    14       // PIN_B5
#define glcdPinData6    15       // PIN_B6
#define glcdPinData7    4        // PIN_B7

#define glcdPinDI       5        // PIN_D0 (i2c SCL)
#define glcdPinRW       6        // PIN_D1 (i2c SDA)
#define glcdPinEN       9        // PIN_C6
#define glcdPinCSEL1    7        // PIN_D2    // normal connection for control signals
#define glcdPinCSEL2    8        // PIN_D3

//#define glcdPinBL       10       // PIN_C7    // optional backlight control pin controls BL circuit
//#define glcdPinRES      17       // PIN_F6    // optional s/w Reset control

#if NBR_CHIP_SELECT_PINS > 2
#error Missing glcdPinCSEL3 define
//#define glcdPinCSEL3    ?   // third chip select if needed
#endif

#if NBR_CHIP_SELECT_PINS > 3
#error Missing glcdPinCSEL4 define
//#define glcdPinCSEL4    ?   // fourth chip select if needed
#endif

//#warning "KS0108 using pins for teensy"

#else
#error "Unsupported teensy processor type"
#endif

#endif //GLCD_PIN_CONFIG_H
