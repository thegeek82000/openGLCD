// 
// openGLCD build information 
// This is a dummy/place-holder header file.
// The information contained here is dummy information that will
// be overwritten by the build scripts when creating an official build.
// The build scripts will stomp on this file and recreate it so the
// only way to add new values to this file is to put them in the build script.
//
// This file only exists so that development and testing on files
// that use these defines can
// be done using a development tree vs having to build an official release.
// 
  
#ifndef __openGLCD_Buildinfo_H__  
#define __openGLCD_Buildinfo_H__  

#define GLCD_GLCDLIB_BUILD_LIBNAMESTR "openGLCD"  // development lib name
  
#define GLCD_GLCDLIB_BUILD_DATESTR __DATE__ " " __TIME__
  
#define GLCD_GLCDLIB_BUILD_BUILDSTR "DevBuild"  // development build string
#define GLCD_GLCDLIB_BUILD_REVSTR "DevRev"  // development rev string
  
#endif 
