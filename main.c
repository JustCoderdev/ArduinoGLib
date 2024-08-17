#include <stdio.h>
#include <stdlib.h>

#include <Arduino.h>
#include <graphics.h>

void tick_to_string(n64 tick, char *text, int max_len)
{
	n8 i;
	for(i = 1; i < max_len; ++i)
	{
		text[max_len - i - 1] = '0' + tick % 10;
		tick -= tick % 10;
		tick /= 10;
	}
}

int main(void)
{
	n64 tick = 0;

	Color background = GRAY;
	Color foreground = TINT_YELLOW;

#if DEBUG_ENABLE
#	define TICK_MAX_LEN (20 + 1)
	char text[TICK_MAX_LEN];
	text[TICK_MAX_LEN - 1] = '\0';
#endif

	GFX_window_initialise();
	while(!GFX_window_should_close())
	{
		GFX_screen_begin();
		GFX_screen_fill(background);

		GFX_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, STROKE, foreground);

#if DEBUG_ENABLE
		tick_to_string(++tick, text, TICK_MAX_LEN);
		GFX_draw_text(text, 2, 2, 6, DEBUG_GRAY, background);
#endif

		GFX_screen_switch();
	}

	GFX_window_finalise();
	return 0;
}
