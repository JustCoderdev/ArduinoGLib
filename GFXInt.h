#ifndef GFXINT_LIB_
#define GFXINT_LIB_

/* mock stuff */
#define GFXRAY_IMP_ 1

#define WIDTH 320
#define HEIGHT 240

typedef unsigned char n8;
typedef unsigned short n16;
typedef unsigned int n32;
typedef unsigned long int n64;

#if(defined(__STDC__) && __STDC_VERSION__ >= 199901L) \
	|| (defined(_MSC_VER) && _MSC_VER >= 1800)
#include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
typedef enum { true = (1 == 1), false = (1 != 1) } bool;
#define RL_BOOL_TYPE
#endif

typedef
#if GFXRAY_IMP_
struct Color {
	n8 r;
	n8 g;
	n8 b;
	n8 a;
}
#elif GFXADA_IMP_
n16
#else
#error AAAAA
#endif
Color;

#if GFXRAY_IMP_
#define RL_COLOR_TYPE
const Color RED = {230, 41, 55, 255};
const Color BLACK = {0, 0, 0, 255};
#elif GFXADA_IMP_
/* R: 0-31 G: 0-63 B: 0-31 */
/* R 230  ==> 230/255*31 = 27.9 = 28  11100  */
/* G  41  ==>  41/255*31 =  4.9 =  5  000101 */
/* B  55  ==>  55/255*31 =  6.6 =  7  00111  */
/* 1110 0000 1010 0111 */
const n16 RED = 0xE0C7; /* {230, 41, 55, 255}; */
const n16 BLACK = 0x0000;
#endif

void GFX_window_initialize(void);
void GFX_window_finalize(void);
bool GFX_window_should_close(void);

void GFX_screen_begin(void);
void GFX_screen_switch(void);
void GFX_screen_fill(Color color);

void GFX_draw_line(
	n16 startPosX, n16 startPosY, n16 endPosX, n16 endPosY, Color color);

void GFX_draw_rect(n16 posX, n16 posY, n16 width, n16 height, Color color);
void GFX_draw_rect_fill(n16 posX, n16 posY, n16 width, n16 height, Color color);

void GFX_draw_text(
	const char *text, int posX, int posY, int fontSize, Color color);

#endif /* GFXINT_LIB_ */
