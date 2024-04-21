#include <stdio.h>

#include "GFXInt.h"
#define GFXRAY_IMP_ 1
/* #define GFXADA_IMP_ 1 */

void printb(n8 byte)
{
	printf("%c%c%c%c%c%c%c%c",
		   byte & 0x80 ? '1' : '0',
		   byte & 0x40 ? '1' : '0',
		   byte & 0x20 ? '1' : '0',
		   byte & 0x10 ? '1' : '0',
		   byte & 0x08 ? '1' : '0',
		   byte & 0x04 ? '1' : '0',
		   byte & 0x02 ? '1' : '0',
		   byte & 0x01 ? '1' : '0');
}

void tick_to_string(n64 tick, char *text, int max_len)
{
	n8 i;
	for(i = 0; i < max_len; ++i)
	{
		text[max_len - i - 1] = '0' + tick % 10;
		tick -= tick % 10;
		tick /= 10;
	}
}

#if 1
int main(void)
{
#define TICK_MAX_LEN (20 + 1)
	n64 tick = 0;
	char text[TICK_MAX_LEN];
	text[TICK_MAX_LEN - 1] = '\0';

	GFX_window_initialize();
	while(!GFX_window_should_close())
	{
		GFX_screen_begin();
		GFX_screen_fill(BLACK);

		GFX_draw_rect_fill(HEIGHT / 2, WIDTH / 2, 1, 1, RED);
		tick_to_string(++tick, text, TICK_MAX_LEN);
		GFX_draw_text(text, 20, 20, 16, RED);

		GFX_screen_switch();
	}

	GFX_window_finalize();
	return 0;
}
#endif
