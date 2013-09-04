/*
 * ks0108_AutoPinConfig.h - automatically select pin config file for board type
 */

#ifndef GLCD_AUTOPINCONFIG_H
#define GLCD_AUTOPINCONFIG_H

 /*
  * The sequence below selects a configuration file for pin assignment based on
  * the board selected in the IDE. These configurations are compatible with
  * wiring used in earlier versions of the library
  * WARNING: When adding new board types it is not as simple as just editing
  * these lines.
  * There is also a dependency on the file glcd/include/glcdio_arduino_io.h
  * which does the actual arduino pin mappings
  */

#if defined(GLCD_CORE_UNO)
#include "config/ks0108_Uno.h"	// config file for standard Arduino Uno/2009/nano
#elif defined(GLCD_CORE_MEGA)
#include "config/ks0108_Mega.h"      // config for mega 1280/2560 board
#elif defined(GLCD_CORE_LEONARDO)
#include "config/ks0108_Leonardo.h"	// config for Leonardo/micro
#elif defined(CORE_TEENSY)
#include "config/ks0108_Teensy.h"	// config for Teensy, Teensy++  and Teensy3
#elif defined(GLCD_CORE_MIGHTY1284P)
#include "config/ks0108_Mighty1284p.h"	// config for "standard" mighty1284p core
#elif defined(GLCD_CORE_SANGUINO)
#include "config/ks0108_Sanguino.h"	// config for Sanguino ATmega644/p or avr_dev mighty1284p core
#elif defined(GLCD_CORE_BOBDUINO)
#include "config/ks0108_Bobduino.h"	// config for bobduino with mighty1284p core
#else
#error Unsupported Arduino board type
#endif

#endif // GLCD_AUTOPINCONFIG_H
