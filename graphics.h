#ifndef GFX_LIB_H_
#define GFX_LIB_H_

/* Types */
typedef unsigned char n8;
typedef unsigned short n16;
typedef unsigned int n32;
typedef unsigned long int n64;

#define DEBUG_ENABLE 1
#define EMULATION_ENABLE 1

#if EMULATION_ENABLE
#define RL_BOOL_TYPE
typedef enum { true = (1 == 1), false = (1 != 1) } bool;
#define RL_COLOR_TYPE
typedef struct Color {
	n8 r, g, b, a;
} Color;
#else
#error "Adafruit not yet implemented :P"
typedef n16 Color;
typedef enum { true = (1 == 1), false = (1 != 1) } bool;
#endif

/* Controls */
extern const int KEY_UP;
extern const int KEY_DOWN;
extern const int KEY_LEFT;
extern const int KEY_RIGHT;
extern const int KEY_OK;

/* Constants */
#define WIDTH 320
#define HEIGHT 240

#define INPUT_DELAY 1500

#define PADDING 10
#define HPADDING (PADDING / 2)
#define DPADDING (2 * PADDING)

#define STROKE 2
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
void GFX_window_initialise(void);
void GFX_window_finalise(void);
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

void GFX_draw_rect(
	n16 posX, n16 posY, n16 width, n16 height, n16 stroke, Color color);

void GFX_draw_rect_fill(n16 posX, n16 posY, n16 width, n16 height, Color color);

void GFX_draw_text(
	const char *text, int posX, int posY, int fontSize, Color color);

#endif /* GFX_LIB_H_ */
