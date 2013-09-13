/*
 * ks0108 GLCDexample
 * (example sketch from original ks0108 library)
 *
 * Basic test code for the Arduino KS0108 GLCD library.
 * This code exercises a range of graphic functions supported
 * by the library and is an example of its use.
 * It also gives an indication of performance, showing the
 *  number of frames drawn per second.  
 */

#include <openGLCD.h>

/*
 * Check for small displays as this code was written
 * before small displays were supported.
 */
#if DISPLAY_HEIGHT < 64
#error ks0108 example requires a display at least 64 pixels tall
#endif
#if DISPLAY_WIDTH < 128
#error ks0108 example requires a display at least 128 pixels wide
#endif

unsigned long startMillis;
unsigned int loops = 0;
unsigned int iter = 0;

void setup(){
  GLCD.Init(NON_INVERTED);   // initialise the library, non inverted writes pixels onto a clear screen
  GLCD.SelectFont(System5x7); // default fixed width system font 

  introScreen();              // show some intro stuff 
  GLCD.ClearScreen();  
  GLCD.DrawBitmap(ArduinoIcon, 32,0); //draw the bitmap at the given x,y position
  countdown(5); 
  GLCD.ClearScreen();
}

void introScreen(){
  GLCD.SelectFont(System5x7); // Font for libname & version
  GLCD.DrawString(GLCD_GLCDLIB_NAMESTR, gTextfmt_center, 3);
  GLCD.DrawString(GLCD_GLCDLIB_VERSIONSTR, gTextfmt_center, GLCD.CharHeight(0) + 3);
  GLCD.DrawRoundRect(0+10,0, GLCD.Width-20, GLCD.CharHeight(0) *2 + 4, 5);  // rounded rectangle around text area   
  GLCD.SelectFont(System5x7); // switch to fixed width system font 
  showCharacters();
  countdown(5);
}

void showCharacters(){
  byte line = 3; // start on the fourth line 
  for(byte c = 32; c <=127; c++){
     if( (c-32) % 20 == 0)
         GLCD.CursorTo(1,line++);  // CursorTo is used for fixed width system font
     GLCD.PutChar(c);    
  }   
}

void drawSpinner(byte pos, byte x, byte y, uint8_t color) {   
  // this draws an object that appears to spin
  switch(pos % 8) {
  case 0 : GLCD.DrawLine( x, y-8, x, y+8, color);      break;
  case 1 : GLCD.DrawLine( x+3, y-7, x-3, y+7, color);  break;
  case 2 : GLCD.DrawLine( x+6, y-6, x-6, y+6, color);  break;
  case 3 : GLCD.DrawLine( x+7, y-3, x-7, y+3, color);  break;
  case 4 : GLCD.DrawLine( x+8, y, x-8, y, color);      break;
  case 5 : GLCD.DrawLine( x+7, y+3, x-7, y-3, color);  break;
  case 6 : GLCD.DrawLine( x+6, y+6, x-6, y-6, color);  break; 
  case 7 : GLCD.DrawLine( x+3, y+7, x-3, y-7, color);  break;
  } 
}

void countdown(int count){
    while(count--){  // do countdown  
     GLCD.CursorTo(0,1);   // first column, second row (offset is from 0)
     GLCD.PutChar(count + '0');
     delay(1000);  
  }  
}

void  loop(){   // run over and over again
  iter = 0;
  startMillis = millis();
  while( millis() - startMillis < 1000){ // loop for one second
    GLCD.DrawRect(0, 0, 65, 64); // rectangle in left side of screen
    GLCD.DrawRoundRect(68, 0, 58, 64, 5);  // rounded rectangle around text area   
    for(int i=0; i < 62; i += 4)
      GLCD.DrawLine(1,1,63,i);  // draw lines from upper left down right side of rectangle  
    GLCD.DrawCircle(32,31,30);   // draw circle centered in the left side of screen  
    drawSpinner(loops++, 100,48, PIXEL_OFF);   // erase spinner position
    drawSpinner(loops,100,48, PIXEL_ON);       // draw new spinner position
    GLCD.CursorTo(5,5);               // locate curser for printing text
    GLCD.PrintNumber(++iter);         // print current iteration at the current cursor position 
  } 
  // display number of iterations in one second
  GLCD.ClearScreen();               // clear the screen  
  GLCD.CursorTo(13,2);              // positon cursor  
  GLCD.Puts("FPS= ");               // print a text string
  GLCD.PrintNumber(iter);           // print a number 
}
