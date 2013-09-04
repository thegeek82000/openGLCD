/*
 * Scribble line drawing sketch
 * adapted from TellyMate scribble Video application client
 *
 * http://www.batsocks.co.uk/downloads/tms_scribble_001.pde
 * 
 */

#include "openGLCD.h"

#define SetPixel(x,y) GLCD.SetDot(x,y,PIXEL_ON)
#define ClearPixel(x,y) GLCD.SetDot(x,y,PIXEL_OFF)

#define SCRIB_WIDTH GLCD.Width
#define SCRIB_HEIGHT GLCD.Height



void setup( void )
{
	GLCD.Init();
}

float g_head_pos = 0.0;

// A binary-friendly increment for the tick variable.
// If it's not binary friendly, then occasional rounding errors mean that the tail of the line
// might not be cleared at the right pixel.
#define TICK 1/128.0

void loop( void )
{
  g_head_pos += TICK ;
  
  float head = g_head_pos ;
  float tail = head - (256 * TICK) ;

  // set the pixels at the 'head' of the line...
  byte x = fn_x( head ) ;
  byte y = fn_y( head ) ;
  SetPixel( x , y ) ;
    
  // clear the pixel at the 'tail' of the line...
  x = fn_x( tail ) ;
  y = fn_y( tail ) ;  
  ClearPixel( x , y ) ;
}


byte fn_x( float tick )
{
  return (byte)(SCRIB_WIDTH/2 + (SCRIB_WIDTH/2-1) * sin( tick * 1.8 ) * cos( tick * 3.2 )) ;
}

byte fn_y( float tick )
{
  return (byte)(SCRIB_HEIGHT/2 + (SCRIB_HEIGHT/2 -1) * cos( tick * 1.2 ) * sin( tick * 3.1 )) ;
}
