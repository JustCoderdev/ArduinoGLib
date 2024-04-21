/* #ifndef GFXRAY_IMP_ */
/* typedef void make_cc_happier; */
/* #endif */

#define GFXRAY_IMP_
#ifdef GFXRAY_IMP_

#include "./lib/raylib.h"
#include "GFXInt.h"

void GFX_window_initialize(void)
{
	InitWindow(WIDTH, HEIGHT, "Display emulator");
}
void GFX_window_finalize(void)
{
	CloseWindow();
}
GFX_bool GFX_window_should_close(void)
{
	if(WindowShouldClose()) return True;
	return False;
}

void GFX_screen_begin(void)
{
	BeginDrawing();
}
void GFX_screen_switch(void)
{
	EndDrawing();
}
void GFX_screen_fill(GFX_Color color)
{
	Color tmp = CLITERAL(Color)(C565TORGB(color));
	ClearBackground(tmp);
}

void GFX_draw_line(
	n16 startPosX, n16 startPosY, n16 endPosX, n16 endPosY, GFX_Color color)
{
	Color tmp = C565TORGB(color);
	DrawLine(startPosX, startPosY, endPosX, endPosY, tmp);
}

void GFX_draw_rect(n16 posX, n16 posY, n16 width, n16 height, GFX_Color color)
{
	Color tmp = {
		255, 255, 255, 255
	};
	DrawRectangleLines(posX, posY, width, height, tmp);
}

void GFX_draw_rect_fill(n16 posX, n16 posY, n16 width, n16 height, GFX_Color color)
{
	DrawRectangle(posX, posY, width, height, color);
}

void GFX_draw_text(
	const char *text, int posX, int posY, int fontSize, Color color)
{
	DrawText(text, posX, posY, fontSize, color);
}
#endif /* GFXRAY_IMP_ */
