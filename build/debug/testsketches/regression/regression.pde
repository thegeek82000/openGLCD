/*
 * regression
 *
 * This is a dummy sketch not intended to ever be run
 * but just compiled to verify that all the API functions exist
 * and support the proper arguments.
 */


#include <openGLCD.h>
#include <include/openGLCD_GLCDv3.h>
#include "fonts/Arial14.h"             // proportional font
#include "fonts/SystemFont5x7.h"       // system font
#include "bitmaps/ArduinoIcon64x64.h"  // 64x64 bitmap 
#include "bitmaps/ArduinoIcon64x32.h"

#include "bitmaps/ArduinoIcon.h"  // 64x64 bitmap

void
setup()
{
	delay(5);    // allow the hardware time settle
	
	GLCD.Init();   // initialise the library, non inverted writes pixels onto a clear screen

	/*
	 * create/restore full display for "default" text area.
	 */
  	GLCD.DefineArea(textAreaFULL);
  	GLCD.SelectFont(System5x7, BLACK);
	GLCD.ClearScreen();
}

void  loop()
{   // run over and over again
}

/*
 * A dummy function to simply check to see if all the API calls still compile
 * It is not intended to actually work or do anything useful.
 */

uint8_t uint8var = 0;

gText predefTA = gText(textAreaBOTTOM);

gText regta;
long longnumber;

char     charstring[] = {'h', 'e', 'l', 'l', 'o', 0x81, 0x82, 0};
uint8_t uint8string[] = {'h', 'e', 'l', 'l', 'o', 0x81, 0x82, 0};

const char     charstring_P[] PROGMEM = {'h', 'e', 'l', 'l', 'o', 0x81, 0x82, 0};
const uint8_t uint8string_P[] PROGMEM = {'h', 'e', 'l', 'l', 'o', 0x81, 0x82, 0};

const char teststring[] PROGMEM = "hello";

#define Fmacro_string F("Hello")


void regression(void)
{

	/*
	 * Control functions.
	 */
	GLCD.Init();
	GLCD.SetDisplayMode(NON_INVERTED);

	/*
	 * Device layer functions.
	 */

	GLCD.GotoXY(0,0);
	GLCD.GotoXY(uint8var, uint8var);
	GLCD.SetDot(0,0, BLACK);
	GLCD.SetDot(uint8var, uint8var, BLACK);
	GLCD.SetPixels(0,0, 20,20, BLACK);
	GLCD.SetPixels(uint8var, uint8var, uint8var, uint8var, BLACK);
	uint8var = GLCD.ReadData();
	GLCD.WriteData(0);
	GLCD.WriteData(uint8var);

	/*
	 * Graphic Functions
	 */
	GLCD.ClearScreen(WHITE);
	GLCD.ClearPage(0, WHITE);
	GLCD.DrawVLine(0,1,2,BLACK);
	GLCD.DrawHLine(0,0, GLCD.Width, BLACK);
	GLCD.DrawLine(0,0, GLCD.Right, GLCD.Bottom, BLACK);
	GLCD.DrawRect(0,0, 10, 10, BLACK);
	GLCD.DrawRoundRect(0, 0, 10, 10, 1, BLACK);
	GLCD.FillRect(0,0, 10, 10, BLACK);
	GLCD.InvertRect(0,0, 10, 10);
	GLCD.DrawCircle(GLCD.CenterX, GLCD.CenterY, 16, BLACK);	
	GLCD.FillCircle(GLCD.CenterX, GLCD.CenterY, 16, BLACK);	

	GLCD.DrawBitmap(ArduinoIcon64x32, 0, 0, BLACK);
	
	/*
	 * check text wrapper functions in GLCD
	 */
	GLCD.SelectFont(System5x7);
	GLCD.SelectFont(Arial_14);

	GLCD.SetFontColor(BLACK); 		// new gText function
	GLCD.SetFontColor(WHITE);		// new gText function
	GLCD.SetTextMode(DEFAULT_gTEXTMODE);	// new gText function
	GLCD.SetTextMode(SCROLL_UP);		// new gtext function
	GLCD.SetTextMode(SCROLL_DOWN);		// new gText function

	GLCD.Puts_P(PSTR("dummy puts_p string"));
	GLCD.Puts_P(charstring_P);
	GLCD.Puts_P((char*)uint8string_P);	// CAST REQRUIRED

	GLCD.CursorTo(0,0);
	GLCD.GotoXY(0,0);			// ks0108 + glcd function
	GLCD.CursorToXY(0,0);			// new gText function

	GLCD.EraseTextLine(eraseTO_EOL);	// new gText function
	GLCD.EraseTextLine(eraseFROM_BOL);	// new gText function
	GLCD.EraseTextLine(eraseFULL_LINE);	// new gText function
	GLCD.EraseTextLine(0);			// new gText function
	

	GLCD.PutChar('c');
	GLCD.PutChar(0xfe);

	GLCD.Puts("dummy puts string");
	GLCD.Puts(charstring);
	GLCD.Puts((char*)uint8string);			// CAST REQRUIRED
	GLCD.Puts(Fmacro_string);
	GLCD.PrintNumber(0);
	GLCD.PrintNumber(longnumber);
	GLCD.printFlash(flashStr("hello"));
	GLCD.printFlashln(flashStr("hello"));
	GLCD.printFlashln(flashStr(""));
	GLCD.printFlashln(FLASHSTRING(teststring));


	GLCD.CharWidth('c');
	GLCD.CharWidth(0xfe);
	GLCD.StringWidth("dummy stringwidth String");
	GLCD.StringWidth(charstring);
	GLCD.StringWidth((char*)uint8string);			// CAST REQUIRED
	GLCD.StringWidth(Fmacro_string);
	GLCD.StringWidth_P(PSTR("dummy stringwidth String"));
	GLCD.StringWidth_P(charstring_P);
	GLCD.StringWidth_P((const char *)uint8string_P);			// CAST REQUIRED
	
	/*
	 * Check aliases
	 */
	GLCD.SelectFont(SystemFont5x7);
	GLCD.SelectFont(Arial14);
	GLCD.DrawBitmap(ArduinoIcon, 0, 0, BLACK);

	/*
	 * Deprecated GLCD functions
	 */
	GLCD.DrawVertLine(0,1,2,BLACK);
	GLCD.DrawHoriLine(0,0, GLCD.Width, BLACK);
	GLCD.ClearSysTextLine(0);
	GLCD.SetInverted(NON_INVERTED);

	/*
	 * check text functions with a user text area.
	 */

	/*
 	 * Text Area functions
	 */
	predefTA.DefineArea(0, 0, GLCD.Right, GLCD.Bottom, SCROLL_UP);
	predefTA.DefineArea(0, 0, 10, 1, SystemFont5x7, SCROLL_UP);
	predefTA.DefineArea(textAreaTOP);

	predefTA.SetTextMode(SCROLL_UP);
	predefTA.SetTextMode(SCROLL_DOWN);

	predefTA.ClearArea();

	predefTA.SelectFont(System5x7);
	predefTA.SelectFont(Arial_14);

	predefTA.SetFontColor(BLACK);
	predefTA.SetFontColor(WHITE);

	predefTA.PutChar('c');
	predefTA.PutChar(0xfe);

	predefTA.Puts("dummy puts string");
	predefTA.Puts(charstring);
	predefTA.Puts((char*)uint8string);				//CAST REQUIRED
	predefTA.Puts(Fmacro_string);
	
	predefTA.Puts_P(PSTR("dummy puts_p string"));
	predefTA.Puts_P(charstring_P);
	predefTA.Puts_P((const char *)uint8string_P);			//CAST REQUIRED
	predefTA.printFlash(flashStr("hello"));
	predefTA.printFlashln(flashStr("hello"));



	predefTA.DrawString("dummy drawstring string",0,0);		// not in GLCD
	predefTA.DrawString(charstring,0,0);				// not in GLCD
	predefTA.DrawString((char*)uint8string,0,0);			// not in GLCD		//CAST REQUIRED
	predefTA.DrawString(Fmacro_string,0,0);
	
	predefTA.DrawString_P(PSTR("dummy drawstring_p string"),0,0);	// not in GLCD
	predefTA.DrawString_P(charstring_P,0,0);			// not in GLCD
	predefTA.DrawString_P((const char*)uint8string_P,0,0);		// not in GLCD		//CAST REQUIRED

	predefTA.write('c');
	predefTA.write(0xfe);

	predefTA.CursorTo(0,0);
	predefTA.CursorTo(-1);		//not in GLCD
	predefTA.CursorToXY(0,0);

	predefTA.CharWidth('c');
	predefTA.CharWidth(0xfe);
	predefTA.StringWidth("dummy stringwidth String");
	predefTA.StringWidth(charstring);
	predefTA.StringWidth((char*)uint8string);		// CAST REQUIRED
	predefTA.StringWidth(Fmacro_string);
	predefTA.StringWidth_P(PSTR("dummy stringwidth String"));
	predefTA.StringWidth_P(charstring_P);
	predefTA.StringWidth_P((const char*)uint8string_P);			// CAST REQUIRED

	predefTA.EraseTextLine(eraseTO_EOL);
	predefTA.EraseTextLine(eraseFROM_BOL);
	predefTA.EraseTextLine(eraseFULL_LINE);
	predefTA.EraseTextLine(0);

#ifndef GLCD_NO_PRINTF
	predefTA.Printf("%s", "hello world\n");

	predefTA.Printf("dummy printf string");
	predefTA.Printf(charstring);
	predefTA.Printf((char*)uint8string);			//CAST REQUIRED
	predefTA.Printf(Fmacro_string);
	
	predefTA.Printf_P(PSTR("dummy printf string"));
	predefTA.Printf_P(charstring_P);
	predefTA.Printf_P((const char *)uint8string_P);			//CAST REQUIRED

#endif

}
