/*
 * Modvk5121_AutoConfig.h - autoconfig file for vk5121 module.
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
#include "debug/bap/config/Modvk5121_BBB_Config.h"   // config file for BBB breadboard configuration
#elif defined(__AVR_ATmega32U4__)// Teensy
#include "debug/bap/config/Modvk5121_TeensyBB_Config.h"    // BreadBoard config for Teensy
#else
#error GLCD vk5121 Autoconfig: Unsupported board type
#endif

#endif
