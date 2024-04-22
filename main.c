#include <stdio.h>

/* #include <math.h> */

#include "./components.h"
#include "./lib/raylib.h"

#define WIDTH 320
#define HEIGHT 240

const Color BLACK = {0};
const Color GRAY = {30, 30, 30, 255};
const Color WHITE = {255, 255, 255, 255};

const Color DEBUG_GRAY = {102, 102, 102, 255};

const Color TINT_RED = {230, 41, 55, 255};
const Color TINT_PINK = {238, 119, 205, 255};
const Color TINT_GREEN = {150, 238, 119, 255};
const Color TINT_BLUE = {119, 152, 238, 255};

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
const Rectangle BORDER = {0, 0, WIDTH, HEIGHT};

#if 1
int main(void)
{
	Color BACKGROUND = GRAY;
	Color FOREGROUND = TINT_RED;
	n32 touch_tick_start = 0;

	n64 selected_item = 0;

#define TICK_MAX_LEN (20 + 1)
	n64 tick = 0;
	char text[TICK_MAX_LEN];
	text[TICK_MAX_LEN - 1] = '\0';

	InitWindow(WIDTH, HEIGHT, "Display emulator");
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BACKGROUND);

		DrawRectangleLinesEx(BORDER, STROKE, FOREGROUND);

		if(IsKeyDown(KEY_DOWN) && tick - touch_tick_start >= KEY_DELAY)
		{
			touch_tick_start = tick;
			selected_item = (selected_item + 1) % ITEMS_COUNT;
		}
		if(IsKeyDown(KEY_UP) && tick - touch_tick_start >= KEY_DELAY)
		{
			touch_tick_start = tick;
			if(selected_item == 0) selected_item = ITEMS_COUNT;
			selected_item--;
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


		tick_to_string(++tick, text, TICK_MAX_LEN);
		DrawText(text, 2, 2, 6, DEBUG_GRAY);

		EndDrawing();
	}

	CloseWindow();
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
