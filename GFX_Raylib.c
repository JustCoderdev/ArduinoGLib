#if EMULATION_ENABLE

#include <assert.h>

#include "graphics.h"
#include "lib/raylib.h"

/* Colors */
const Color BLACK = {0};
const Color GRAY = {30, 30, 30, 255};
const Color WHITE = {255, 255, 255, 255};

const Color DEBUG_GRAY = {102, 102, 102, 255};

const Color TINT_RED = {230, 41, 55, 255};
const Color TINT_PINK = {238, 119, 205, 255};
const Color TINT_GREEN = {150, 238, 119, 255};
const Color TINT_YELLOW = {253, 249, 0, 255};
const Color TINT_BLUE = {119, 152, 238, 255};

/* Controls */
const int KEY_UP = 'K';
const int KEY_DOWN = 'J';
const int KEY_LEFT = 'H';
const int KEY_RIGHT = 'L';
const int KEY_OK = 257;

/* Window */
void GFX_window_initialize(void)
{
	InitWindow(WIDTH, HEIGHT, "Display emulator");
}
void GFX_window_finalize(void)
{
	CloseWindow();
}
bool GFX_window_should_close(void)
{
	return WindowShouldClose();
}

/* Screen */
void GFX_screen_begin(void)
{
	BeginDrawing();
}
void GFX_screen_switch(void)
{
	EndDrawing();
}
void GFX_screen_fill(Color color)
{
	ClearBackground(color);
}

/* Input */
bool GFX_input_key_is_pressed(int key)
{
	return IsKeyPressed(key);
}

bool GFX_input_key_is_down(int key)
{
	return IsKeyDown(key);
}

bool GFX_input_key_is_released(int key)
{
	return IsKeyReleased(key);
}

/* Drawing */
void GFX_draw_line(n16 startPosX,
				   n16 startPosY,
				   n16 endPosX,
				   n16 endPosY,
				   n16 stroke,
				   Color color)
{
	assert(0 && "GFX_draw_line not implemented");
}

void GFX_draw_rect(
	n16 posX, n16 posY, n16 width, n16 height, n16 stroke, Color color)
{
	Rectangle rectangle = {0};
	rectangle.x = posX;
	rectangle.y = posY;
	rectangle.width = width;
	rectangle.height = height;

	DrawRectangleLinesEx(rectangle, stroke, color);
}
void GFX_draw_rect_fill(n16 posX, n16 posY, n16 width, n16 height, Color color)
{
	DrawRectangle(posX, posY, width, height, color);
}

void GFX_draw_text(
	const char *text, int posX, int posY, int fontSize, Color color)
{
	DrawText(text, posX, posY, fontSize, color);
}

#endif
