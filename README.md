# Arduino GLib

An attempt to write a GFX_API for Arduino with support to run an emulator powered by Raylib

## Interface

```c
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

/* Drawing */
void GFX_draw_line(n16 startPosX, n16 startPosY, n16 endPosX, n16 endPosY,
                   n16 stroke, Color color);

void GFX_draw_rect(n16 posX, n16 posY, n16 width, n16 height, n16 stroke,
                   Color color);

void GFX_draw_rect_fill(n16 posX, n16 posY, n16 width, n16 height, Color color);

void GFX_draw_round_rect(n16 posX, n16 posY, n16 width, n16 height, n16 stroke,
                         float roundness, Color color);

void GFX_draw_round_rect_fill(n16 posX, n16 posY, n16 width, n16 height,
                              float roundness, Color color);

void GFX_draw_text(const char *text, int posX, int posY, int fontSize,
                   Color foreground, Color background);
```
