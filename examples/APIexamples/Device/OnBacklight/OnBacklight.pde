/*
 * OnBacklight - openGLCD API example
 *
 * Example of using:
 * OnBacklight()
 * OffBacklight()
 *
 * status = OnBacklight();
 * status = OffBacklight();
 *
 * OnBacklight() turns on the backlight if backlight control is configured
 * OffBacklight() turns off the backlight if backlight control is configured
 *
 * Note: Backlight control also requires additional circuitry
 *
 *
 * N-CH Mosfet version: (More costly but less power draw and lower part count)
 * ---------------------------------------------------------------------------
 *
 *                (value depends on GLCD, 100ohm is usually safe)
 * (LCD BL anode)---[ resistor ]---(VCC)
 *
 * (LCD BL cathode)---------------+
 *                                |
 *                                D
 *                                |
 * (BL input)----------------G-|-< (2N7000 FET)
 *                                |
 *                                S
 *                                |
 *                              (GND)
 *
 * NOTE: Gate resistor not needed as the mosfet is voltage fed and only really
 *       pulls current while switching.
 *
 * Here are two example backlight circuits that can be used:
 *
 *
 * NPN Transistor version: (Cheaper but more power draw and higher part count)
 * ---------------------------------------------------------------------------
 *
 *                (value depends on GLCD, 100ohm is usually safe)
 * (LCD BL anode)---[ resistor ]---(VCC)
 *
 * (LCD BL cathode)---------------+
 *                                |
 *                                C
 *                                |
 * (BL input)--[ Resistor ]---B-|> (NPN) 2N2222A/2N3904 etc...
 *                  1k            |
 *                                E
 *                                |
 *                              (GND)
 *
 * NOTE: The Base resistor is needed because the NPN is current fed.  For lower
 *       power draw, try a 10k resistor.
 *
 * In either case, when the BL input is HIGH the LCD backlight will turn on.
 *
 * 
 * Created by Bill Perry 2013-08-01
 * bperrybap@opensource.billsworld.billandterrie.com
 */

#include <openGLCD.h>

void setup()
{

	GLCD.Init();
	GLCD.SelectFont(System5x7);
}

void loop(void)
{
int status;

	GLCD.DrawString("OnBacklight", gTextfmt_center, gTextfmt_center, eraseFULL_LINE);
	status = GLCD.OnBacklight();  // turn on backlight (if configured)
	if(status != GLCD_ENOERR)
	{
		 // failed, code here handles error, if needed
		 // status GLCD_ENOTSUPPORTED if not configured
		GLCD.DrawString("(unsupported)", gTextfmt_center, gTextfmt_bottom, eraseFULL_LINE);
	}
	else
	{
		// Only do OffBacklight if OnBacklight worked

		delay(2000);

		GLCD.ClearScreen();
		GLCD.DrawString("OffBacklight", gTextfmt_center, gTextfmt_center, eraseFULL_LINE);
		status = GLCD.OffBacklight();  // turn off backlight (if configured)
		if(status != GLCD_ENOERR)
		{
			 // failed, code here handles error, if needed
			 // status GLCD_ENOTSUPPORTED if not configured
		}
	}
	delay(1000);
}
