/*
  sed1520_Device.h - openGLCD library support for graphic LCDs 

 vi:ts=4
  
*/

#ifndef GLCD_PANEL_DEVICE_H
#define GLCD_PANEL_DEVICE_H

/*
 * define name for Device
 */
#ifdef GLCD_MT12232D_MODE
#define glcdDev_DeviceName "sed1520-mt12232d"
#else
#define glcdDev_DeviceName "sed1520"
#endif

/*
 * Sanity check SED1520 config info
 */

#if (CHIP_WIDTH < DISPLAY_WIDTH) && (CHIP_HEIGHT !=  DISPLAY_HEIGHT)
#error "SED1520 CHIP_WIDTH < DISPLAY_WITDH but CHIP_HEIGHT != DISPLAY_HEIGHT"
#endif

#if (CHIP_HEIGHT < DISPLAY_HEIGHT) && (CHIP_WIDTH !=  DISPLAY_WIDTH)
#error "SED1520 CHIP_HEIGHT < DISPLAY_HEIGHT but CHIP_WIDTH != DISPLAY_WIDTH"
#endif

#if (CHIP_HEIGHT == DISPLAY_HEIGHT) && (DISPLAY_WIDTH != 2 * CHIP_WIDTH)
#error "SED1520 CHIP_HEIGHT == DISPLAY_HEIGHT but DISPLAY_WIDTH != 2 * CHIP_WIDTH"
#endif

#if defined(glcdPinEN) && defined(glcdPinE1) 
#error "SED1520 configuration cannot use both glcdPinEN and glcdPinE1"
#endif

#if defined(glcdPinEN) && defined(glcdPinE2) 
#error "SED1520 configuration cannot use both glcdPinEN and glcdPinE2"
#endif

#if defined(glcdPinE2) && !defined(glcdPinE1) 
#error "SED1520 configuration missing glcdPinE1"
#endif

#if defined(glcdPinE1) && !defined(glcdPinE2) 
#error "SED1520 configuration missing glcdPinE2"
#endif

#if !defined(glcdPinE1) && !defined(glcdPinE2) & !defined(glcdPinEN)
#error "SED1520 configuration requires an enable pin"
#endif

#if (defined(glcdPinE1) || defined(glcdPinE2)) && defined(glcd_CHIP0)
#error "SED1520 cannot use glcdPinE1 or glcdPinE2 with glcd_CHIP0"
#endif

#if (defined(glcdPinE1) || defined(glcdPinE2)) && defined(glcd_CHIP0)
#error "SED1520 cannot use glcdPinE1 or glcdPinE2 with glcd_CHIP0"
#endif

#if (defined(glcdPinE1) || defined(glcdPinE2)) && defined(glcd_CHIP1)
#error "SED1520 cannot use glcdPinE1 or glcdPinE2 with glcd_CHIP1"
#endif

#if defined(glcdPinEN) && (!defined(glcd_CHIP0) || !defined(glcd_CHIP1))
#error "SED1520 glcdPinEN requires glcd_CHIP0 and glcd_CHIP1"
#endif

// requires at least one CSEL pin
#if defined(glcdPinEN) && !defined(glcdPinCSEL1)
#error "SED1520 glcdPinEN requires glcdPinCSEL1"
#endif

/*
 * LCD commands -------------------------------------------------------------
 */

#define LCD_ON				0xAF
#define LCD_OFF            	0xAE
#define LCD_DISP_START		0xC0	// set display START line
#define LCD_SET_ADD        	0x00	// set column (Segment) address
#define LCD_SET_PAGE		0xB8
#define LCD_RESET			0xE2	// Reset is a command not a signal
#define LCD_ADC_RIGHTWARD	0xA0		
#define LCD_ADC_LEFTWARD	0xA1		
#define LCD_STATICDRIVE_OFF	0xA4	// Normal operation
#define LCD_STATICDRIVE_ON	0xA5	// static drive all segments lit (power save)
#define LCD_DUTY_16			0xA8	// 1/16 duty factor for driving LCD cells
#define LCD_DUTY_32			0xA9	// 1/32 duty factor for driving LCD cells
#define LCD_RMW				0xE0	// start RMW mode
#define LCD_RMW_END			0xEE	// end RMW mode

/*
 * Status register bits/flags -----------------------------------------------
 */

#define LCD_BUSY_FLAG		0x80 
#define LCD_BUSY_BIT		7
#define LCD_ADC_FLAG		0x40	// ADC status 1 = nomral /forward 0=leftward/reverse
#define LCD_ADC_BIT			6		// ADC status 1 = nomral /forward 0=leftward/reverse

#define LCD_RESET_BIT		4
#define LCD_RESET_FLAG		0x10

/*
 * Define primitives used by glcd_Device.cpp --------------------------------
 */

/*
 * Check for chipselects
 */
#ifdef glcd_CHIP0
#define glcdDev_SelectChip(chip) SelectChip(chip)
#else
#define glcdDev_SelectChip(chip)
#endif

/*
 *	For now Assume only 2 chips
 *
 *	This assumption will also keep from doing a
 *	true modulo function to detect chip crossover
 *	as the chipwidth is not a power of two which
 *	means that masking cannot be used in place
 *  of real division.
 */


/*
 * Check for single E line or seperate E lines.
 */
#ifdef glcdPinEN // single enable
#define glcdDev_ENstrobeHi(chip) glcdio_WritePin(glcdPinEN, 1)
#define glcdDev_ENstrobeLo(chip) glcdio_WritePin(glcdPinEN, 0)

#else

#define glcdDev_ENstrobeHi(chip) 	\
do									\
{									\
	if(chip == 0)					\
       glcdio_WritePin(glcdPinE1, HIGH);	\
	else							\
       glcdio_WritePin(glcdPinE2, HIGH);	\
}while(0)

#define glcdDev_ENstrobeLo(chip) 	\
do									\
{									\
	if(chip == 0)					\
	   glcdio_WritePin(glcdPinE1, LOW);	\
	else							\
	   glcdio_WritePin(glcdPinE2, LOW);	\
}while(0)
#endif



/*
 * Convert X & Y coordinate to chip values
 */

#if CHIP_HEIGHT < DISPLAY_HEIGHT
#define glcdDev_XYval2Chip(x, y)	(((y) < CHIP_HEIGHT) ? 0 : 1)
#else
#define glcdDev_XYval2Chip(x, y)	(((x) < CHIP_WIDTH) ? 0 : 1)
#endif

/*
 * check for special MT12232d mode
 */
#ifndef GLCD_MT12232D_MODE

#define glcdDev_Xval2ChipCol(x)		((x) < CHIP_WIDTH ? x : (x - CHIP_WIDTH))

#else

/*
 * MT12232d doesn't use/need a chip # to strobe EN
 * as there is only a single EN line, so ignore the chip parameter.
 * However, E is acive low so strobe is "backwards" with respect to levels.
 */

#undef glcdDev_ENstrobeHi
#undef glcdDev_ENstrobeLo
#define glcdDev_ENstrobeHi(chip) glcdio_WritePin(glcdPinEN, 0)
#define glcdDev_ENstrobeLo(chip) glcdio_WritePin(glcdPinEN, 1)

/*
 * Special code for MT12232D module
 * column must be offset by 0x13. So that is why the column is offset by 0x13 for chip 0 below.
 */

#define glcdDev_Xval2ChipCol(x)		((x) < CHIP_WIDTH ? (x + 0x13) : (x - CHIP_WIDTH))

/*
 * Custom init routine
 * md12232d module is VERY funky!
 * The left side is mapped backwards so you have to set ADC=1 for chip 0
 * Then when using ADC=1 there is a 0x13 column offset (handled by glcdDev_Xval2ChipCol() above )
 */
#define glcdDev_Init(chip)					\
({												\
uint8_t status;									\
	do												\
	{												\
		WriteCommand(LCD_RMW_END, chip);			\
		WriteCommand(LCD_ON, chip);					\
		WriteCommand(LCD_DISP_START, chip);			\
		if(chip == 0)								\
		   WriteCommand(LCD_ADC_LEFTWARD, chip);	\
		else										\
		   WriteCommand(LCD_ADC_RIGHTWARD, chip);	\
	}while(0);										\
	status = GLCD_ENOERR;							\
	status;	/* return value of macro */				\
})

#endif // GLCD_MT12232D_MODE



#endif //GLCD_PANEL_DEVICE_H
