#if !EMULATION_ENABLE

#include <graphics.h>
#include <MCUFRIEND_kbv.h>

/* Colors */
const Color BLACK = 0x0000;
const Color GRAY = 0x20E4;
const Color WHITE =  0xFFFF;

const Color DEBUG_GRAY = 0x632C;

const Color TINT_RED    = 0xE147;
const Color TINT_PINK   =  0xEBB9;
const Color TINT_GREEN  = 0x976E;
const Color TINT_YELLOW =  0xFFA0;
const Color TINT_BLUE   =  0x74BD;

/* Controls */
const n32 KEY_UP = 'K';
const n32 KEY_DOWN = 'J';
const n32 KEY_LEFT = 'H';
const n32 KEY_RIGHT = 'L';
const n32 KEY_OK = 257;

/* Implementation specific stuff */
#define PORTRAIT 0
#define LANDSCAPE 3
#define PORTRAIT_REV 2
#define LANDSCAPE_REV 1

MCUFRIEND_kbv screen {A3, A2, A1, A0, A4};

void GFX_window_initialise(void)
{
	screen.begin(screen.readID());
	screen.setRotation(LANDSCAPE);

	if (SCREEN_WIDTH != screen.width() || SCREEN_HEIGHT != screen.height())
	{
		/* Serial.println("[FATAL] WIDTH or HEIGHT mismatch"); */
		/* death_screen_show(); */
	}
}
void GFX_window_finalise(void) {}
bool GFX_window_should_close(void)
{
	return false;
}

/* Screen */
void GFX_screen_begin(void) {
	screen.startWrite();
}
void GFX_screen_switch(void) {
	screen.endWrite();
}

void GFX_screen_fill(Color color)
{
	screen.fillScreen(color);
}

/* Input */
bool GFX_input_key_is_pressed(int key)
{
	return false;
}
bool GFX_input_key_is_down(int key)
{
	return false;
}
bool GFX_input_key_is_released(int key)
{
	return false;
}

n32 GFX_input_key_pressed_next()
{
	return 0;
}

/* Drawing */
void GFX_draw_line(n16 startPosX, n16 startPosY, n16 endPosX, n16 endPosY,
                   n16 stroke, Color color)
{
    screen.drawLine(startPosX, startPosY, endPosX, endPosY, color);
}

void GFX_draw_rect(n16 posX, n16 posY, n16 width, n16 height, n16 stroke,
                   Color color)
{

    screen.drawRect(posX, posY, width, height, color);
}

void GFX_draw_rect_fill(n16 posX, n16 posY, n16 width, n16 height, Color color)
{
	screen.fillRect(posX, posY, width, height, color);
}

void GFX_draw_round_rect(n16 posX, n16 posY, n16 width, n16 height, n16 stroke,
                         float roundness, Color color)
{
	screen.drawRoundRect(posX, posY, width, height, roundness, color);
}

void GFX_draw_round_rect_fill(n16 posX, n16 posY, n16 width, n16 height,
                              float roundness, Color color)
{
	screen.fillRoundRect(posX, posY, width, height, roundness, color);
}

void GFX_draw_text(const char *text, int posX, int posY, int fontSize,
                   Color foreground, Color background)
{
	screen.drawChar(posX, posY, *text, foreground, background, fontSize);
}

#endif
