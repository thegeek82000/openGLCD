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
 * Created by Bill Perry 2013-08-01
 * bperrybap@opensource.billsworld.billandterrie.com
 */

#include <openGLCD.h>
void FillRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color)
{
  	int16_t tSwitch; 
	uint8_t x1 = 0, y1 = radius;
  	tSwitch = 3 - 2 * radius;
	
	while (x1 <= y1)
	{
#define DRAW
#ifdef DRAW
//	    GLCD.SetDot(x+radius - x1, y+radius - y1, color);
	    GLCD.DrawLine(x+radius - x1, y+radius - y1, x+radius, y+radius-y1, color);
	    GLCD.DrawLine(x+radius - y1, y+radius - x1, x+radius, y+radius-x1, color);
//	    GLCD.SetDot(x+radius - y1, y+radius - x1, color);
#ifdef notdef

	    this->SetDot(x+width-radius + x1, y+radius - y1, color);
	    this->SetDot(x+width-radius + y1, y+radius - x1, color);
	    
	    this->SetDot(x+width-radius + x1, y+height-radius + y1, color);
	    this->SetDot(x+width-radius + y1, y+height-radius + x1, color);

	    this->SetDot(x+radius - x1, y+height-radius + y1, color);
	    this->SetDot(x+radius - y1, y+height-radius + x1, color);
#endif
#else
	    GLCD.DrawLine(x+radius - x1, y+radius - y1, x+radius - y1, y+radius - x1, color);

	    GLCD.DrawLine(x+width-radius + x1, y+radius - y1, x+width-radius + y1, y+radius - x1, color);
	    
	    GLCD.DrawLine(x+width-radius + x1, y+height-radius + y1, x+width-radius + y1, y+height-radius + x1, color);

	    GLCD.DrawLine(x+radius - x1, y+height-radius + y1, x+radius - y1, y+height-radius + x1, color);
#endif

	    if (tSwitch < 0) {
	    	tSwitch += (4 * x1 + 6);
	    } else {
	    	tSwitch += (4 * (x1 - y1) + 10);
	    	y1--;
	    }
	    x1++;
	}
	  	
#if 0
	this->DrawHLine(x+radius, y, width-(2*radius), color);			// top
	this->DrawHLine(x+radius, y+height, width-(2*radius), color);	// bottom
	this->DrawVLine(x, y+radius, height-(2*radius), color);			// left
	this->DrawVLine(x+width, y+radius, height-(2*radius), color);	// right
#endif
	GLCD.DrawHLine(x+radius, y, width-(2*radius), color);			// top
	GLCD.DrawHLine(x+radius, y+height, width-(2*radius), color);	// bottom
	GLCD.DrawVLine(x, y+radius, height-(2*radius), color);			// left
	GLCD.DrawVLine(x+width, y+radius, height-(2*radius), color);	// right

}


void setup()
{

    GLCD.Init();
}

void loop(void)
{
	GLCD.ClearScreen();


	delay(1000);

	FillRoundRect(GLCD.Left,GLCD.Top, GLCD.Right, GLCD.Bottom, 10, BLACK);
	
#ifdef notdef
	/*
	 * Draw rectangles on the display every 4 pixels starting
	 * from the outsided and move in.
	 */
	for(uint8_t i = 0; i < GLCD.Bottom/2; i +=4)
	{
		GLCD.DrawRect(GLCD.Left + i,GLCD.Top+i, GLCD.Right - 2*i, GLCD.Bottom - 2*i);
		delay(200);
	}
#endif
	delay(2000);
}
