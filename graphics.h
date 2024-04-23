#ifndef GFX_LIB_H_
#define GFX_LIB_H_

#define GRAPHICS_EMULATION 1

#ifdef GRAPHICS_EMULATION
typedef enum { true = (1 == 1), false = (1 != 1) } bool;
#define RL_BOOL_TYPE
struct Color;
#else
#error Adafruit not yet implemented :P
typedef n16 Color;
typedef enum { true = (1 == 1), false = (1 != 1) } bool;
#endif

/* Types */
typedef unsigned char n8;
typedef unsigned short n16;
typedef unsigned int n32;
typedef unsigned long int n64;

/* Controls */
const int KEY_UP;
const int KEY_DOWN;
const int KEY_LEFT;
const int KEY_RIGHT;
const int KEY_OK;

/* Constants */
#define WIDTH  320
#define HEIGHT 240

#define KEY_DELAY 1500

#define PADDING	 10
#define HPADDING (PADDING / 2)
#define DPADDING (2 * PADDING)

#define STROKE	2
#define HSTROKE (STROKE / 2)
#define DSTROKE (2 * STROKE)

/* Colors */
extern const Color BLACK;
extern const Color GRAY;
extern const Color WHITE;

extern const Color DEBUG_GRAY;

extern const Color TINT_RED;
extern const Color TINT_PINK;
extern const Color TINT_GREEN;
extern const Color TINT_YELLOW;
extern const Color TINT_BLUE;

/* Window */
void GFX_window_initialize(void);
void GFX_window_finalize(void);
bool GFX_window_should_close(void);

/* Screen */
void GFX_screen_begin(void);
void GFX_screen_switch(void);
void GFX_screen_fill(Color color);

/* Input */
bool GFX_input_key_is_pressed(int key);
bool GFX_input_key_is_down(int key);
bool GFX_input_key_is_released(int key);

/* Drawing */
void GFX_draw_line(n16 startPosX,
				   n16 startPosY,
				   n16 endPosX,
				   n16 endPosY,
				   n16 stroke,
				   Color color);

void GFX_draw_rect(n16 posX,
				   n16 posY,
				   n16 width,
				   n16 height,
				   n16 stroke,
				   Color color);

void GFX_draw_rect_fill(n16 posX, n16 posY, n16 width, n16 height, Color color);

void GFX_draw_text(const char *text,
				   int posX,
				   int posY,
				   int fontSize,
				   Color color);

#endif /* GFX_LIB_H_ */
