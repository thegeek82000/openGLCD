
//#define BAPDEBUG_WRITE
//#define BAPDEBUG_WRITECMD
//#define BAPDEBUG_READ
//#define BAPDEBUG_BUSY
//#define BAPDEBUG_GOTO
//#define BAPDEBUG_SELECT

//#define BAPDEBUG_BADVALUES


#define BAPDEBUG

extern "C" {
#include <inttypes.h>
#include <stdio.h>      // BAPDEBUG
}

#if defined(__AVR_ATmega32U4__) ||defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#include "usb_api.h"

#else

#include "HardwareSerial.h"     // BAPDEBUG

#endif

static char buf[64];
#define bapprintf(...)                                             \
        do {                                                    \
                sprintf(buf, __VA_ARGS__); Serial.write(buf);   \
        } while (0)


#define kbwait() \
        do {                                                    \
                bapprintf("Press any key to contiue....");         \
                Serial.flush();                                 \
                while(Serial.available() == 0)                  \
					;											\
                Serial.flush();                                 \
                bapprintf("<OK>\n");                                   \
        } while (0)


#define DBG(fmt, ...)\
        Serial.printf("%s:%d: " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);

