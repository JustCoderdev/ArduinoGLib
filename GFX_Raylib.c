#include <stdio.h>

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
const n32 KEY_LEFT = 'H';
const n32 KEY_DOWN = 'J';
const n32 KEY_UP = 'K';
const n32 KEY_RIGHT = 'L';
const n32 KEY_OK = 257; /* Enter */

/* Window */
void GFX_window_initialise(void)
{
	InitWindow(WIDTH, HEIGHT, "Display emulator");
}
void GFX_window_finalise(void)
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
	if(IsKeyPressed(key))
	{
#if DEBUG_ENABLE
		printf("Key pressed (%d)\n", key);
#endif
		return true;
	}

	return false;
}

bool GFX_input_key_is_down(int key)
{
	/* Weird issue, solution here
	 * <https://www.reddit.com/r/raylib/comments/rwjyym/iskeydown_always_returns_true>
	 */
	bool keyStatus = (char)IsKeyDown(key);

	/* Status for J: 573973504 -  (0)Key down (74) */
	/* printf("Status for %c: %d - %c (%d)", */
	/*        key, keyStatus, (char)keyStatus, (char)keyStatus); */

	if(keyStatus)
	{
#if DEBUG_ENABLE
		printf("Key down (%d)\n", key);
#endif
		return true;
	}

	return false;
}

bool GFX_input_key_is_released(int key)
{
	if(IsKeyReleased(key))
	{
#if DEBUG_ENABLE
		printf("Key released (%d)\n", key);
#endif
		return true;
	}

	return false;
}

n32 GFX_input_key_pressed_next()
{
	return GetKeyPressed();
}

/* Drawing */
void GFX_draw_line(n16 startPosX, n16 startPosY, n16 endPosX, n16 endPosY,
                   n16 stroke, Color color)
{
	Vector2 startPos = {0};
	Vector2 endPos = {0};

	startPos.x = startPosX;
	startPos.y = startPosY;

	endPos.x = endPosX;
	endPos.y = endPosY;

	DrawLineEx(startPos, endPos, stroke, color);
}

void GFX_draw_rect(n16 posX, n16 posY, n16 width, n16 height, n16 stroke,
                   Color color)
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

void GFX_draw_round_rect(n16 posX, n16 posY, n16 width, n16 height, n16 stroke,
                         float roundness, Color color)
{
	Rectangle rectangle = {0};
	rectangle.x = posX;
	rectangle.y = posY;
	rectangle.width = width;
	rectangle.height = height;

	DrawRectangleRoundedLines(rectangle, roundness, 20, stroke, color);
}

void GFX_draw_round_rect_fill(n16 posX, n16 posY, n16 width, n16 height,
                               float roundness, Color color)
{
	Rectangle rectangle = {0};
	rectangle.x = posX;
	rectangle.y = posY;
	rectangle.width = width;
	rectangle.height = height;

	DrawRectangleRounded(rectangle, roundness, 20, color);
}

void GFX_draw_text(const char *text, int posX, int posY, int fontSize,
                   Color color)
{
	DrawText(text, posX, posY, fontSize, color);
}
