#include <stdio.h>

#include "./components.h"
#include "./graphics.h"

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
	{"Item10", 6},
	{"Item11", 6},
	{"Item12", 6},
	{"Item13", 6},
	{"Item14", 6},
	{"Item15", 6},
	{"Item16", 6},
	{"Item17", 6},
	{"Item18", 6},
};
const n8 ITEMS_COUNT = ARRAY_LEN(ITEMS, ListItem);
n64 tick = 0;

typedef enum { SELECTOR, DETAIL } State;

#if 1
int main(void)
{
	Color BACKGROUND = GRAY;
	Color FOREGROUND = TINT_RED;

	State app_state = SELECTOR;

	n32 touch_tick_start = 0;
	n64 selected_item = 0;

/* DEBUG */
#define TICK_MAX_LEN (20 + 1)
	char text[TICK_MAX_LEN];
	text[TICK_MAX_LEN - 1] = '\0';
	/* DEBUG */

	GFX_window_initialize();
	while(!GFX_window_should_close())
	{
		GFX_screen_begin();
		GFX_screen_fill(BACKGROUND);

		GFX_draw_rect(0, 0, WIDTH, HEIGHT, STROKE, FOREGROUND);

		switch(app_state)
		{
			case SELECTOR:
				FOREGROUND = TINT_RED;

				if(GFX_input_key_is_down(KEY_DOWN)
				   && tick - touch_tick_start >= KEY_DELAY)
				{
					touch_tick_start = tick;
					selected_item = (selected_item + 1) % ITEMS_COUNT;
				}
				if(GFX_input_key_is_down(KEY_UP)
				   && tick - touch_tick_start >= KEY_DELAY)
				{
					touch_tick_start = tick;
					if(selected_item == 0) selected_item = ITEMS_COUNT;
					(selected_item)--;
				}

				ListView(PADDING + STROKE,
						 PADDING + STROKE,
						 WIDTH - DPADDING - 4,
						 HEIGHT - DPADDING - 4,
						 ITEMS,
						 ITEMS_COUNT,
						 &selected_item,
						 FOREGROUND,
						 BACKGROUND);

				if(GFX_input_key_is_pressed(KEY_OK)
				   && tick - touch_tick_start >= KEY_DELAY)
				{
					touch_tick_start = tick;
					printf("OK: Item (%lu)\n", selected_item);
					printf("%s\n", ITEMS[selected_item].text);
					app_state = DETAIL;
				}
				break;

			case DETAIL:
				FOREGROUND = TINT_YELLOW;
				GFX_draw_text(ITEMS[selected_item].text,
							  WIDTH / 2 - DPADDING,
							  HEIGHT / 2,
							  20,
							  FOREGROUND);

				if(GFX_input_key_is_pressed(KEY_LEFT))
				{
					app_state = SELECTOR;
					printf("OK: Item (%lu)\n", selected_item);
					printf("%s\n", ITEMS[selected_item].text);
				}
				break;
		}

		tick_to_string(++tick, text, TICK_MAX_LEN);
		GFX_draw_text(text, 2, 2, 6, DEBUG_GRAY);

		GFX_screen_switch();
	}

	GFX_window_finalize();
	return 0;
}
#endif

/* n16 RGBTO565(n8 R, n8 G, n8 B) */
/* { */
/* 	n16 r, g, b; */

/* 	/1* rrrrrggg gggbbbbb *1/ */
/* 	r = roundf((float)R / 255 * 31); */
/* 	g = roundf((float)G / 255 * 63); */
/* 	b = roundf((float)B / 255 * 31); */
/* 	/1* R 230  ==> 230/255*31 = 27.9 = 28   11100  *1/ */
/* 	/1* G  41  ==>  41/255*63 = 10.1 = 10  001010 *1/ */
/* 	/1* B  55  ==>  55/255*31 =  6.6 =  7   00111  *1/ */

/* 	return (r << 11) | (g << 5) | b; */
/* } */

/* Color C565TORGB(n16 C565) */
/* { */
/* 	Color tmp = {0}; */
/* 	tmp.r = roundf((float)((C565 & 0xF800) >> 11) / 31 * 255); */
/* 	tmp.g = roundf((float)((C565 & 0x07E0) >> 5) / 63 * 255); */
/* 	tmp.b = roundf((float)(C565 & 0x001F) / 31 * 255); */
/* 	tmp.a = 255; */

/* 	return tmp; */
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
