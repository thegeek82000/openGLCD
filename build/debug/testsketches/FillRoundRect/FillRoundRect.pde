/*
 * FillRoundRect - openGLCD API example
 *
 * Example of using:
 * FillRoundRect()
 *
 * DrawRect(x,y, width, height, [color]);
 *
 * Draw a filled rectangle with the specified width and height.
 * The upper left corner at x,y and lower cornder at x+width, y+width.
 * The length of the horizontal sides will be width +1 pixels.
 * The length of the vertical sides will height +1 pixels.
 *
 * Created by Bill Perry 2013-09-04
 * bperrybap@opensource.billsworld.billandterrie.com
 */

#include <openGLCD.h>

void setup()
{

    GLCD.Init();
}

void loop(void)
{
	GLCD.ClearScreen();

	delay(1000);

	GLCD.FillRoundRect(GLCD.Left,GLCD.Top, GLCD.Width, GLCD.Height, 10, BLACK);
	
	delay(2000);
}
