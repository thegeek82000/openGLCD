/*
 * SetBacklight - openGLCD API example
 *
 * Example of using:
 * SetBacklight()
 *
 * status = SetBacklight();
 *
 * SetBacklight() Sets the backlight brightness
 *
 * If the display circuitry only has the option to turn the 
 * backlight on and off  then any non zero value will turn the display on
 * with maximum brightness
 * The value HIGH should not be used to turn the backlight on since
 * this function is used to control backlight intensity and not
 * for on / off control.
 * A value of HIGH is typically 1 which would be a very dim backlight.
 *
 * Note: Backlight control requires additional circuitry
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

	GLCD.DrawString("SetBacklight", gTextfmt_center, gTextfmt_center);
	int status = GLCD.OnBacklight(); // turn on full bight backlight (if configured)
	if(status != GLCD_ENOERR)
	{
		// failed, code here handles error, if needed
		// status GLCD_ENOTSUPPORTED if not configured
		GLCD.DrawString("(unsupported)", gTextfmt_center, gTextfmt_bottom);
	}
	else
	{
		// only do intensity test if backlight control works
		delay(1000);

		/*
		 * Ramp the intensity down, then back up
		 */

		for(int times = 0; times < 3; times++)
		{
			for(int x = 1; x < 16; x++)
			{
				status = GLCD.SetBacklight(256-x * 16);
				if(status != GLCD_ENOERR)
				{
					// failed, code here handles error, if needed
					// status GLCD_ENOTSUPPORTED if not configured
				}
				delay(45);
			}
			for(int x = 1; x < 16; x++)
			{
				status = GLCD.SetBacklight(x * 16);
				if(status != GLCD_ENOERR)
				{
					// failed, code here handles error, if needed
					// status GLCD_ENOTSUPPORTED if not configured
				}
				delay(45);
			}
		}
	}
	delay(1000);
}
