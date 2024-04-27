#include <stdio.h>
#include <stdlib.h>

#include "components.h"
#include "graphics.h"

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

#define ARRAY_LEN(ARRAY, ITEM) (sizeof(ARRAY) / sizeof(ITEM))
const ListItem ITEMS[] = {
    {"Item1", 6},
    {"Item2", 6},
    {"Item3", 6},
    {"Item4", 6},
    {"Item5", 6},
    {"Item6", 6},
    {"Item7", 6},
    {"Item8", 6},
    {"Item9", 6},
    {"ItemA", 6},
    {"ItemB", 6},
    {"ItemC", 6},
    {"ItemD", 6},
    {"ItemE", 6},
    {"ItemF", 6},
};
const n8 ITEMS_COUNT = ARRAY_LEN(ITEMS, ListItem);

int main(void)
{
	n64 tick = 0;
	n8  i;

	Color background = GRAY;
	Color foreground = TINT_RED;

	typedef enum { VIEW_LIST, VIEW_DETAIL } View;
	View current_view = VIEW_LIST;

	n64 selected_idx = 0;
	n64 input_start = 0;

	bool autoload = true;
	n64  current_progress = 0;
	n64  total_progress = 1000;

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

		GFX_draw_rect(0, 0, WIDTH, HEIGHT, STROKE, foreground);

		switch(current_view)
		{
			case VIEW_LIST:
				foreground = TINT_RED;

				/* Handle input */
				if(tick - input_start >= INPUT_DELAY
				   && GFX_input_key_is_down(KEY_DOWN))
				{
					input_start = tick;
					selected_idx = (selected_idx + 1) % ITEMS_COUNT;
				}

				if(tick - input_start >= INPUT_DELAY
				   && GFX_input_key_is_down(KEY_UP))
				{
					input_start = tick;
					if(selected_idx == 0) selected_idx = ITEMS_COUNT;
					(selected_idx)--;
				}

				if(GFX_input_key_is_pressed(KEY_OK)
				   || GFX_input_key_is_pressed(KEY_RIGHT))
				{
					printf("OK: Item (%lu) %s\n",
					       selected_idx,
					       ITEMS[selected_idx].text);

					current_view = VIEW_DETAIL;
				}

				/* Render UI */
				ListView(PADDING + STROKE,
				         PADDING + STROKE,
				         WIDTH - DPADDING - DSTROKE,
				         HEIGHT - DPADDING - DSTROKE,
				         ITEMS,
				         ITEMS_COUNT,
				         &selected_idx,
				         foreground,
				         background);
				break;

			case VIEW_DETAIL:
				foreground = TINT_YELLOW;

				/* Handle input */
				if(GFX_input_key_is_pressed(KEY_OK))
				{
					autoload = !autoload;
				}

				if(tick - input_start >= INPUT_DELAY
				   && GFX_input_key_is_down(KEY_RIGHT))
				{
					input_start = tick;
					current_progress = (current_progress + 20) % total_progress;
				}

				if(autoload && tick % 200 == 0)
					current_progress = (current_progress + 1) % total_progress;

				/* Draw UI */
				GFX_draw_text(ITEMS[selected_idx].text,
				              HWIDTH - DPADDING,
				              HHEIGHT - DPADDING,
				              20,
				              foreground);

				LoadingBar(WIDTH / 4,
				           HHEIGHT - 4 - STROKE + DPADDING,
				           HWIDTH,
				           8,
				           current_progress,
				           total_progress,
				           foreground,
				           background);

				if(!autoload)
				{
					GFX_draw_text("Stopped loading",
					              HWIDTH - DPADDING * 2,
					              HHEIGHT + 8 + STROKE + DPADDING,
					              12,
					              TINT_RED);
				}
				else
				{
#define BUFF_LEN 32
					char  buffer[BUFF_LEN] = {0};
					float progress_perc
					    = (float)current_progress / total_progress * 100;
					char string_len = snprintf(
					    buffer, BUFF_LEN, "Loading... %0.0f%%", progress_perc);

					if(string_len < 0)
					{
						printf("ERROR formatting Loading text");
					}
#undef BUFF_LEN

					GFX_draw_text(buffer,
					              HWIDTH - PADDING * 3,
					              HHEIGHT + 8 + STROKE + DPADDING,
					              12,
					              foreground);
				}

				/* Exit logic */
				if(GFX_input_key_is_pressed(KEY_LEFT))
				{
					current_view = VIEW_LIST;
				}
				break;
		}

#if DEBUG_ENABLE
		tick_to_string(++tick, text, TICK_MAX_LEN);
		GFX_draw_text(text, 2, 2, 6, DEBUG_GRAY);
#endif

		GFX_screen_switch();
	}

	GFX_window_finalise();
	return 0;
}

/* Color C565TORGB(n16 C565) */
/* { */
/* 	Color tmp = {0}; */
/* 	tmp.r = roundf((float)((C565 & 0xF800) >> 11) / 31 * 255); */
/* 	tmp.g = roundf((float)((C565 & 0x07E0) >> 5) / 63 * 255); */
/* 	tmp.b = roundf((float)(C565 & 0x001F) / 31 * 255); */
/* 	tmp.a = 255; */

/* 	return tmp; */
/* } */

/* n16 round_(float value) */
/* { */
/* 	n64   truncated = (n64)value; */
/* 	float remainder = value - truncated; */

/* 	return truncated + (remainder > 0.6); */
/* } */
/* n16 RGBTO565(n8 R, n8 G, n8 B) */
/* { */
/* 	n16 r, g, b; */

/* 	/1* rrrrrggg gggbbbbb *1/ */
/* 	r = round_((float)R / 255 * 31); */
/* 	g = round_((float)G / 255 * 63); */
/* 	b = round_((float)B / 255 * 31); */
/* 	/1* R 230  ==> 230/255*31 = 27.9 = 28   11100  *1/ */
/* 	/1* G  41  ==>  41/255*63 = 10.1 = 10  001010 *1/ */
/* 	/1* B  55  ==>  55/255*31 =  6.6 =  7   00111  *1/ */

/* 	return (r << 11) | (g << 5) | b; */
/* } */

/* void printb(n8 byte) */
/* { */
/* 	printf("%c%c%c%c%c%c%c%c", */
/* 		   byte & 0x80 ? '1' : '0', */
/* 		   byte & 0x40 ? '1' : '0', */
/* 		   byte & 0x20 ? '1' : '0', */
/* 		   byte & 0x10 ? '1' : '0', */
/* 		   byte & 0x08 ? '1' : '0', */
/* 		   byte & 0x04 ? '1' : '0', */
/* 		   byte & 0x02 ? '1' : '0', */
/* 		   byte & 0x01 ? '1' : '0'); */
/* } */
