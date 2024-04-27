#include "./graphics.h"

#if !EMULATION_ENABLE

/* Colors */
const Color BLACK = {0};                  /* 0x0000 */
const Color GRAY = {30, 30, 30, 255};     /* 0x20E4 */
const Color WHITE = {255, 255, 255, 255}; /* 0xFFFF */

const Color DEBUG_GRAY = {102, 102, 102, 255}; /* 0x632C */

const Color TINT_RED = {230, 41, 55, 255}; /* 0xE147 */
const Color TINT_PINK = {238, 119, 205, 255};  /* 0xEBB9 */
const Color TINT_GREEN = {150, 238, 119, 255}; /* 0x976E */
const Color TINT_YELLOW = {253, 249, 0, 255};  /* 0xFFA0 */
const Color TINT_BLUE = {119, 152, 238, 255};  /* 0x74BD */

/* Controls */
const int KEY_UP = 'K';
const int KEY_DOWN = 'J';
const int KEY_LEFT = 'H';
const int KEY_RIGHT = 'L';
const int KEY_OK = 257;

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
void GFX_draw_line(n16 startPosX, n16 startPosY, n16 endPosX, n16 endPosY,
                   n16 stroke, Color color);

void GFX_draw_rect(n16 posX, n16 posY, n16 width, n16 height, n16 stroke,
                   Color color);
void GFX_draw_rect_fill(n16 posX, n16 posY, n16 width, n16 height, Color color);

void GFX_draw_text(const char *text, int posX, int posY, int fontSize,
                   Color color);

#endif
