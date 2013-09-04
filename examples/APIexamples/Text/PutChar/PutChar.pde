/*
 * PutChar - openGLCD API example
 *
 * Example of using:
 * PutChar()
 *
 * status = PutChar(c)
 * c     - character to output
 *
 * If the character will not fit on the current text line
 * inside the text area,
 * the text position is wrapped to the next line. This might be
 * the next lower or the next higher line depending on the
 * scroll direction.
 *
 * If there is not enough room to fit a full line of new text after
 * wrapping, the entire text area will be scrolled to make room for a new
 * line of text. The scroll direction will be up or down
 * depending on the scroll direction for the text area.
 *
 * If there is an attempt to output a character that has no definition
 * i.e. its width is zero in the font data, then no character will be rendered.
 * This occurs if the font is a "sparse" font, that does not define all the char
 *
 * Returns:
 *  1 if a character was rendered, 0 if a character was not rendered
 *
 * Created by Bill Perry 2013-08-01
 * bperrybap@opensource.billsworld.billandterrie.com
 */

#include <openGLCD.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/cp437font8x8.h>

#define DELAY 3000 // ms delay between examples

/*
 * Create a text area for each of the 4 quadrants
 */
gText textArea[4];

void setup()
{
	GLCD.Init();
	GLCD.SelectFont(System5x7); // use system in "default" text area
	/*
	 * Create the text area regions in each quadrant and assign font
	 */
	textArea[0].DefineArea(textAreaTOPLEFT, cp437font8x8);
	textArea[1].DefineArea(textAreaTOPRIGHT, cp437font8x8);
	textArea[2].DefineArea(textAreaBOTTOMLEFT, cp437font8x8);
	textArea[3].DefineArea(textAreaBOTTOMRIGHT, cp437font8x8);

}

void ClearAreas()
{

	/*
	 * Clear all the text areas
	 */
	for(uint8_t i = 0; i < 4; i++)
	{
		textArea[i].ClearArea();
	}
}
	

void loop()
{
	/*
	 * Put text in center of display using default text area
	 */

	GLCD.DrawString(F("PutChar"), gTextfmt_center, gTextfmt_center);
	delay(DELAY);

	GLCD.println(); // wrap to new line
	/*
	 * Output all the characters beween ASCII <SPACE> 0x20 and 0x7f
	 * to the default text area. Wraping/Scrolling will occur as needed.
	 */
	for(uint8_t c = 0x20; c < 0x80; c++)
	{
		GLCD.PutChar(c);
		delay(50); // slow down for effect
	}

	delay(DELAY);
	ClearAreas();

	textArea[0].PutChar(0x03); // cp437 heart symbol
	delay(500);
	textArea[0].println(" heart");
	textArea[0].PutChar(0x01); // cp437 smile symbol
	delay(500);
	textArea[0].print(" smile");
	delay(300);

	textArea[1].PutChar(0x0b); // cp437 male symbol
	delay(500);
	textArea[1].println(" boy");
	textArea[1].PutChar(0x0c); // cp437 female symbol
	delay(500);
	textArea[1].print(" girl");
	delay(300);

	textArea[2].PutChar(0x0d); // cp437 note symbol
	delay(500);
	textArea[2].println(" note");
	textArea[2].PutChar(0x9b); // cp437 cent symbol
	delay(500);
	textArea[2].println(" cent");
	delay(300);

	textArea[3].PutChar(0xe3); // cp437 pi symbol
	delay(500);
	textArea[3].println(" pi");
	textArea[3].PutChar(0xea); // cp437 ohm symbol
	delay(500);
	textArea[3].print(" ohm");
	delay(300);

	delay(DELAY);
	ClearAreas();
}
