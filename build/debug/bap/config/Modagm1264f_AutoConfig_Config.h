/*
 * ks0108_AutoConfig.h - autoconfig file for BGmicro module.
 *
 * vi:ts=8
 *
 * This file is used to automatically select configurations based on Arduino IDE "board" type
 * Currently this based on the AVR processor type.
 *
 */

#ifndef	glcd_AUTOCONFIG_H
#define glcd_AUTOCONFIG_H

/*
 * The code below selects a configuration file based on the board selected in the IDE 
 * These configurations are compatable with wiring used in earlier versions of the library
 * 
 */


#if defined (__AVR_ATmega328P__ ) || defined(__AVR_ATmega168P__)
#include "build/debug/bap/config/Modagm1264f_BBB_Config.h"   // config file for BBB breadboard configuration
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__) || defined(__AVR_ATmega32U4__)// Teensy
#include "build/debug/bap/config/Modagm1264f_TeensyBB_Config.h"    // BreadBoard config for Teensy and Teensy++  
#else
#error GLCD ks0108 (BG micro) Autoconfig: Unsupported board type
#endif

#endif
