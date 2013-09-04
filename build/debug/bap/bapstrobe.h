
#include "include/arduino_io.h"
#include "include/avrio.h"


#define BAPSTROBE(pin)  \
	do {avrio_PinMode(pin, 1); avrio_WritePin(pin, 1); avrio_WritePin(pin,0);} while(0)

#ifndef BAPSTROBE
#define BAPSTROBE(pin)
#endif

#define BAPSTROBE_S(pin) BAPSTROBE(pin)


#define BAPSTROBE_E(pin) do { BAPSTROBE(pin); BAPSTROBE(pin); } while(0)

