#ifndef GFXINT_LIB_
#define GFXINT_LIB_

#include <stdio.h>

#include <math.h>

/* mock stuff */
/* #define GFXRAY_IMP_ 1 */

#define WIDTH 320
#define HEIGHT 240

typedef unsigned char n8;
typedef unsigned short n16;
typedef unsigned int n32;
typedef unsigned long int n64;

/* 00000000 000rrrrr */
/* rrrrr000 00gggggg */
/* rrrrrggg gggbbbbb */
#define RGBTO565(R, G, B)                                                    \
	(round((float)(R) / 255 * 31) << 11) | (round((float)G / 255 * 63) << 5) \
		| round((float)B / 255 * 31);

#define C565TORGB(HEX)                       \
	{                                        \
	round((HEX & 0xF800) >> 11) / 31 * 255), \
	round(((HEX & 0x07E0) >> 5) / 63 * 255), \
	round((HEX & 0x001F) / 31 * 255)         \
	255                                      \
	}

typedef n16 GFX_Color;

#if(defined(__STDC__) && __STDC_VERSION__ >= 199901L) \
	|| (defined(_MSC_VER) && _MSC_VER >= 1800)
#include <stdbool.h>
typedef bool GFX_bool;
#elif RL_BOOL_TYPE
#error multiple bool definition
typedef enum bool GFX_bool;
#elif !defined(__cplusplus) && !defined(bool)
typedef enum { True = (1 == 1), False = (1 != 1) } GFX_bool;
#endif

/* R: 0-31 G: 0-63 B: 0-31 */
/* R 230  ==> 230/255*31 = 27.9 = 28  11100  */
/* G  41  ==>  41/255*31 =  4.9 =  5  000101 */
/* B  55  ==>  55/255*31 =  6.6 =  7  00111  */
/* 1110 0000 1010 0111 */
const n16 RED = 0xE0C7; /* {230, 41, 55, 255}; */
const n16 BLACK = 0x0000;

/* R 230  ==> 230/255*31 = 27.9 = 28   11100  */
/* G  41  ==>  41/255*63 = 10.1 = 10  001010 */
/* B  55  ==>  55/255*31 =  6.6 =  7   00111  */

void GFX_window_initialize(void);
void GFX_window_finalize(void);
GFX_bool GFX_window_should_close(void);

void GFX_screen_begin(void);
void GFX_screen_switch(void);
void GFX_screen_fill(GFX_Color color);

void GFX_draw_line(
	n16 startPosX, n16 startPosY, n16 endPosX, n16 endPosY, GFX_Color color);

void GFX_draw_rect(n16 posX, n16 posY, n16 width, n16 height, GFX_Color color);
void GFX_draw_rect_fill(
	n16 posX, n16 posY, n16 width, n16 height, GFX_Color color);

void GFX_draw_text(
	const char *text, int posX, int posY, int fontSize, GFX_Color color);

#endif /* GFXINT_LIB_ */
