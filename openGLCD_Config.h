/*
 * openGLCD_Config.h - User specific configuration for openGLCD library
 *
 * This file is shipped to automatically configure the library for a 
 * 128x64 ks0108 panel using the wiring described in the documentation.
 *
 * Use this file to select the active configuration file
 * Then edit the selected panel file to configure parameters for that panel.
 *
 * For Teensy devices the default wiring matches the wiring documented
 * on the Teensy website.
 * http://www.pjrc.com/teensy/td_libs_GLCD.html
 *
 */

#ifndef openGLCD_CONFIG_H
#define openGLCD_CONFIG_H

/*
 * Include core definitions
 */
#if ARDUINO < 100
#if ARDUINO < 19
#error openGLCD requires Arduino 0019 or later
#endif
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

#include "include/glcd_arduino_io.h" // set up openGLCD Arduino core i/o defines for autoconfig

 /*
  * Select a configuration file by uncommenting one line to include the
  * the desired configuration file.
  *
  * Select 1 and only 1 configuration file.
  *
  * The "AutoConfig" configuration files will configure the library based on a set of
  * pre-customized configurations for the supported Arduino board type. 
  *
  * These configurations match the the panel and pin configurations
  * in the library documentation based on the type of board selected in the Arduino IDE.
  *
  * NOTE: if you have a panel that has different dimensions than the distributed configuration, you can either
  * edit the supplied configuration file for that board type or create a fully custom configuration file.
  *
  * The auto configuration file (default is named  "config/ks0108_Panel.h") selects the appropriate board
  * pin configuration file based on the current board selection in the Arduino IDE.
  *   
  * The auto configuration panel configuration files can be found under the "config" directory,
  * with a seperate directory for the files related to each panel type.
  * The naming is:
  *  config/{PANELNAME}/AutoConfig_"{PANELNAME}-{MODELNAME}_Panel.h"
  * Where:
  *   {PANELNAME} is the glcd panel type. (for example, ks0108)
  *   -{MODELNAME} is optional and is a model name of the glcd (for example, 128x64, JHD19264A)
  *
  * The pin configuration files for each board type can also be found in the same directory, the naming is:
  *  config/{PANELNAME}/"PinConfig_{PANELNAME}-{BOARDNAME}.h"
  * Where:
  *   {PANELNAME} is the glcd panel type. (for example, ks0108)
  *   {BOARDNAME} is the name of the Arduino board (or board family as selected in the Arduino IDE).
  *
  * So for example, the auto configuration file name for the default ks0108 panel
  * is: "config/ks0108/AutoConfig_ks0108-128x64_Panel.h"
  * The ks0108 pin configuration file for a "Uno" board is:
  *  "config/ks0108/PinConfig_ks0108-Uno.h"
  * The pin configuration file for a "Mega" board:
  *  "config/ks0108/PinConfig_ks0108-Mega.h"
  * Teensy boards are an exception as all boards share a common pinconfig file:
  *  "config/ks0108/PinConfig_ks0108-Teensy.h"
  * 
  */

/***********************************************************************************************************
 *
 * Additional "autoconfig" files can be created, there is an example for 192x64 panels in this distribution.
 * In the future there will be more for different panel types, like sed1520, ks0713, etc..
 *
 ***********************************************************************************************************/


 /*
  * autoconfig includes - (comment this out if using manual configurations, see below)
  */
#include "config/ks0108/AutoConfig_ks0108-128x64_Panel.h"    // automatically configure library for a ks0108 128x64 panel
//#include "config/ks0108/AutoConfig_ks0108-192x64_Panel.h"    // automatically configure library for a ks0108 192x64 panel
//#include "config/ks0108/AutoConfig_ks0108-JHD19264A_Panel.h" // automatically configure library for a ks0108 JHD19264A panel
//#include "config/ks0108/AutoConfig_ks0108-HJ19264A_Panel.h"  // automatically configure library for a ks0108 HJ19264A panel
//#include "config/hd44102/AutoConfig_hd44102_Panel.h"    

/*
 * If you want to explicitly select a manual configuration, you can edit the desired manual configuration
 * to fill in or modify the configuration information to meet your needs.
 * You can also use these files as a template to make customized copies to hold specific configurations.
 *
 * Remember that to activate your manual configuration you uncomment the #include for the desired file
 * and make sure that all the other config  #includes are commented (including the autoconfig above) 
 */

//#include "config/ks0108/ManualConfig_ks0108_Panel.h"       // generic ks0108 configuration

//#include "config/ks0108/ManualConfig_ks0108-agm1264f_Panel.h"  // configuration for BGMicro 128x64 display with pinout diagram
//#include "config/sed1520/ManualConfig_sed1520-vk5121_Panel.h"  // configuration for vk5121 122x32 display with pinout diagram
//#include "config/mt12232d/ManualConfig_mt12232d_Panel.h" // configuration for Russian mt12232 display with pinout diagram

/*
 * For debugging
 */
//#include "build/debug/bap/bapdebug.h"
//#include "build/debug/bap/config/Modvk5121_AutoConfig_Config.h"
//#include "build/debug/bap/config/Modagm1264f_AutoConfig_Config.h"
//#include "build/debug/bap/config/Modagm1264f_TeensyBB128_Config.h"


/*========================== Optional User Defines ==================================*/

//#define GLCDCFG_NO_PRINTF	// disable xxprintf() support

//#define GLCDCFG_NO_SCROLLDOWN // disable reverse scrolling (saves ~600 bytes of code on AVR)
                                // This will allow those tight on FLASH space to save a bit of code space

//#define GLCDCFG_ATOMIC_IO	// Generate code that ensures all pin i/o operations are atomic
                                // including any potential nibble operations.
                                // Without this option enabled, nibble operations will be slightly faster but
                                // might have issues if a pin used shares a processor i/o port with an
                                // interrupt routine that updates pins/bits on the same port.


//#define GLCDCFG_NODEFER_SCROLL // uncomment to disable deferred newline processing

//#define GLCDCFG_NOINIT_CHECKS	// uncomment to remove initialization busy status checks
				// this turns off the code in the low level init code that
				// checks for a module stuck BUSY or stuck in RESET.
				// This will save about 100 bytes of code space (on AVR) in normal sketches.
				// and an additional 220 bytes in the diag sketch. This will cause
				// diags to hang if wires are not correct vs return an error.

//#define GLCDCFG_READ_CACHE	// Turns on code that uses a frame buffer for a read cache
				// This adds only ~52 bytes of code (on AVR) but...
				// will use DISPLAY_HEIGHT/8 * DISPLAY_WIDTH bytes of RAM
				// A typical 128x64 ks0108 will use 1k of RAM for this.
				// performance increase is quite noticeable (double or so on FPS test)
				// This will not work on smaller AVRs like the mega168 that only
				// have 1k of RAM total.

/*========================== End of Optional User Defines ==================================*/


/*
 * do not modify below here
 */

#if 1

#if defined (__AVR__)
// Workaround for http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34734
// to prevent: warning: only initialized variables can be placed into program memory area
// In order to use this on AVR, ALL progmem variables must be declared the same with respect
// to const since they will land in the same section. So all progmem variables should use const.

#ifdef PROGMEM
//#undef PROGMEM
//#define PROGMEM __attribute__((section(".progmem.data")))
#endif
#define PROGMEMGLCD __attribute__((section(".progmem.openGLCD")))

#else // non AVR
#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".rodata"))) // put into read-only data section so it doesn't end up in RAM
#endif

#endif

#if __AVR__
#define GLCDFONTDECL(_n) const uint8_t PROGMEMGLCD _n[]
#define GLCDBMAPDECL(_n) const uint8_t PROGMEMGLCD _n[]
#define GLCDXBMAPDECL(_n) const uint8_t PROGMEMGLCD _n[]
#else
#define GLCDFONTDECL(_n) const uint8_t _n[]
#define GLCDBMAPDECL(_n) const uint8_t _n[]
#define GLCDXBMAPDECL(_n) const uint8_t _n[]
#endif

#endif // CONSIDER

/*
 * Kludge macros for missing stuff in ChipKit 
 */

#if defined(__PIC32MX__)
#ifndef PGM_P
#define PGM_P const char *
#endif
#ifndef PSTR
#define 	PSTR(s)   ((const char *)(s))
#endif
#endif // __PIC32MX__

#endif  // openGLCD_CONFIG_h
