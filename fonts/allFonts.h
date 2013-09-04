/*
 * allFonts.h font header for GLCD library 
 * The fonts listed below will be available in a sketch if this file is included
 *
 * If you create your own fonts you can add the header to this file
 *
 * Note that the build environment only holds a font in Flash if its selected 
 * so there is no penalty to including a font file here if its not used 
 */

#ifndef _allFonts_h_
#define _allFonts_h_

#include "SystemFont5x7.h"      // system font (fixed width)
#include "Iain5x7.h"		// similar to system5x7 but proportional
#include "Arial14.h"            // proportional font
#include "Arial_bold_14.h"      // Bold proportional font
#include "Corsiva_12.h"
#include "Verdana_digits_24.h"  // large proportional font contains [0-9] and :

#include "fixednums7x15.h"       // fixed width font - + , - . / [0-9] and :
#include "fixednums8x16.h"       // fixed width font - + , - . / [0-9] and :
#include "fixednums15x31.h"      // fixed width font - + , - . / [0-9] and :

#include "CalBlk36.h"
#include "CalLite24.h"
#include "lcdnums12x16.h"	// font that looks like LCD digits
#include "lcdnums14x24.h"	// font that looks like LCD digits
#include "fixed_bold10x15.h"
#include "Wendy3x5.h"

/*
 * These fonts require new no-pad rendering code
 */
#include "font8x8.h"		// fixed wider font but similar to system5x7 font
#include "cp437font8x8.h"        // fixed Font from 80's IBM PC

#endif
