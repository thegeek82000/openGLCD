/*
 * clockFace.pde
 *
 * analog clock using the openGLCD library
 *
 * uses pushbuttons to set the time
 * defualt connections are pins 2 and 3
 * connect one side of a button to a pin, the other side to ground
 * one button advances time forward, the other moves it back
 *
 * 2013.06.15 bperrybap        - bug fixes, updates to work with
 *                               openGLCD & teensy3
 *                               enhanced anamimation when no buttons being used
 * 2010 Michael Margolis       - original creation
 */

// uncomment to enable using Arduino pins with 
// grounding pushbuttons attached to set clock hands

//#define btnForward 2 // buttons to set clock hands
//#define btnBack 3
 
#include <openGLCD.h>    // Graphics LCD library   

/*
 * download Time library from:
 *  http://www.arduino.cc/playground/Code/Time
 *  http://www.pjrc.com/teensy/td_libs_Time.html (recommended)
 */
#include <Time.h>
#include "AnalogClock.h"  // header file for the analog clock class

#define PULL_UP  HIGH

AnalogClock analogClock = AnalogClock();  // this creates an instance of the analog clock display. 

void setup(){
#ifdef btnForward
  digitalWrite(btnForward, PULL_UP);  // enable internal pull-up resistors
#endif
#ifdef btnBack
  digitalWrite(btnBack, PULL_UP);  
#endif

  GLCD.Init(); // start the GLCD code
  GLCD.SelectFont(System5x7);

  setTime(4,37,0,2,1,10); // set time to 4:37 am Jan 2 2010  
  analogClock.Init(GLCD.CenterX,GLCD.CenterY,GLCD.CenterY-4);  // draw the clock face  
}

void  loop(){  
  time_t  prevtime;
  prevtime = now(); 
  while( prevtime == now() )
  {
    // check if set buttons pressed while waiting for second to rollover
#ifdef btnForward
    checkSetButton(btnForward, 1);    
#else
    checkSetButton(-1, 1);    // dummy call to simulate button pushed to advance time
#endif
#ifdef btnBack
    checkSetButton(btnBack, -1);
#endif
  }
#if (DISPLAY_HEIGHT < 64)
// small clocks scribble over numbers so redraw face
  analogClock.DrawFace();
#endif
  analogClock.DisplayTime(hour(), minute(), second() ); // update analog clock  
}


void checkSetButton(int button, int direction)
{
const int stepSecs[] = {1,30,300};  // values used to accelerate movement when button held down
int stepIndex = 0; // the index to determine accelartion value
int step = 0; // counts steps between each index increment

  if((button == -1) || digitalRead(button)== LOW)
  {
     delay(50);  // debounce time     
     unsigned long startTime = millis() + 1000;
     while((button == -1) || digitalRead(button)== LOW)
     {
       if(millis() - startTime > 100){
         startTime = millis();
         adjustTime(stepSecs[stepIndex] * direction);
#if (DISPLAY_HEIGHT < 64)
// small clocks scribble over numbers so redraw face
         analogClock.DrawFace();
#endif
         analogClock.DisplayTime(hour(), minute(), second() ); // update analog clock  
         if( ++step > 30){
            step=0;
            if(stepIndex < 2){
               stepIndex++; 
            }
         }        
       }
     } 
  }   
}
