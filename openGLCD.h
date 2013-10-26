#ifndef __openGLCD_H__
#define __openGLCD_H__

#include <include/glcd_types.h>
#include <include/glcd.h>
#include <include/glcd_errno.h>
#include <openGLCD_Buildinfo.h>

#include <fonts/allFonts.h>
#include <bitmaps/allBitmaps.h>

#define GLCD_GLCDLIB_NAMESTR "openGLCD" // name of library

// library version
// get it from the build info
#define GLCD_GLCDLIB_VERSIONSTR GLCD_GLCDLIB_BUILD_REVSTR

#endif // __openGLCD_H__
