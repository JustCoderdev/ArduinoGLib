#include <stdio.h>

#include <math.h>

#include "./lib/raylib.h"

#define WIDTH 320
#define HEIGHT 240

typedef unsigned char n8;
typedef unsigned short n16;
typedef unsigned int n32;
typedef unsigned long int n64;

n16 RGBTO565(n8 R, n8 G, n8 B)
{
	n16 r, g, b;

	/* rrrrrggg gggbbbbb */
	r = roundf((float)R / 255 * 31);
	g = roundf((float)G / 255 * 63);
	b = roundf((float)B / 255 * 31);
	/* R 230  ==> 230/255*31 = 27.9 = 28   11100  */
	/* G  41  ==>  41/255*63 = 10.1 = 10  001010 */
	/* B  55  ==>  55/255*31 =  6.6 =  7   00111  */

	return (r << 11) | (g << 5) | b;
}

Color C565TORGB(n16 C565)
{
	Color tmp = {0};
	tmp.r = roundf((float)((C565 & 0xF800) >> 11) / 31 * 255);
	tmp.g = roundf((float)((C565 & 0x07E0) >> 5) / 63 * 255);
	tmp.b = roundf((float)(C565 & 0x001F) / 31 * 255);
	tmp.a = 255;

	return tmp;
}

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
	for(i = 1; i < max_len; ++i)
	{
		text[max_len - i - 1] = '0' + tick % 10;
		tick -= tick % 10;
		tick /= 10;
	}
}

/* Controls
 * UP - DOWN
 * LEFT - RIGHT
 * OK
 * */
#define KEY_DELAY 1500
#define KEY_UP ((int)'K')
#define KEY_DOWN ((int)'J')
#define KEY_LEFT ((int)'H')
#define KEY_RIGHT ((int)'L')
#define KEY_OK KEY_ENTER

const Color BLACK = {0};
const Color GRAY = {30, 30, 30, 255};
const Color WHITE = {255, 255, 255, 255};

const Color DEBUG_GRAY = {102, 102, 102, 255};

const Color TINT_RED = {230, 41, 55, 255};
const Color TINT_PINK = {238, 119, 205, 255};
const Color TINT_GREEN = {150, 238, 119, 255};
const Color TINT_BLUE = {119, 152, 238, 255};

typedef struct {
	char *text;
	n8 text_len;
} ListItem;

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

const n16 PADDING = 10;
const n16 DPADDING = 2 * PADDING;
const Rectangle BORDER = {0, 0, WIDTH, HEIGHT};

const n16 LIST_HEIGHT = HEIGHT - DPADDING - 2;
const n16 LIST_WIDTH = WIDTH - DPADDING - 2;
const n16 LIST_REL_X = PADDING + 2;
const n16 LIST_REL_Y = PADDING + 2;
const Rectangle LIST_BORDER = {
	LIST_REL_X,
	LIST_REL_Y,
	LIST_WIDTH,
	LIST_HEIGHT,
};

const n16 LIST_BAR_WIDTH = 15;
const n16 LIST_BAR_HEIGHT = LIST_HEIGHT;
const n16 LIST_BAR_REL_X = WIDTH - PADDING - LIST_BAR_WIDTH;
const n16 LIST_BAR_REL_Y = LIST_REL_Y;
const Rectangle LIST_BAR_BORDER = {
	LIST_BAR_REL_X,
	LIST_BAR_REL_Y,
	LIST_BAR_WIDTH,
	LIST_BAR_HEIGHT,
};

const n16 LIST_CURSOR_HEIGHT = (LIST_BAR_HEIGHT / ITEMS_COUNT);
const n16 LIST_CURSOR_HEIGHT_REST = (LIST_BAR_HEIGHT % ITEMS_COUNT);

const n16 LIST_ITEM_MARGIN = 6;

const n16 LIST_ITEM_FONT_SIZE = 20;
const n16 LIST_ITEM_HEIGHT = 25;
const n16 LIST_ITEM_MAX_WIDTH = LIST_WIDTH - LIST_BAR_WIDTH - PADDING;
const n16 LIST_MAX_ITEMS = LIST_HEIGHT / (LIST_ITEM_HEIGHT + LIST_ITEM_MARGIN);

/* TODO: Fix rounding error */
const n16 LIST_ITEM_HEIGHT_REST =
	LIST_HEIGHT % (LIST_ITEM_HEIGHT + LIST_ITEM_MARGIN);

#if 1
int main(void)
{
	Color BACKGROUND = GRAY;
	Color FOREGROUND = TINT_RED;

	n8 selected_item = 0;
	n8 offset_item = 0;
	n32 touch_tick_start = 0;
	n16 i;

#define TICK_MAX_LEN (20 + 1)
	n64 tick = 0;
	char text[TICK_MAX_LEN];
	text[TICK_MAX_LEN - 1] = '\0';

	BACKGROUND = GRAY;
	FOREGROUND = TINT_RED;

	InitWindow(WIDTH, HEIGHT, "Display emulator");
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BACKGROUND);

		tick_to_string(++tick, text, TICK_MAX_LEN);
		DrawText(text, 20, HEIGHT - 20, 16, DEBUG_GRAY);

		DrawRectangleLinesEx(BORDER, 2, FOREGROUND);
		DrawRectangleLinesEx(LIST_BAR_BORDER, 2, FOREGROUND);
		DrawRectangle(LIST_BAR_REL_X,
					  LIST_BAR_REL_Y + selected_item * LIST_CURSOR_HEIGHT,
					  LIST_BAR_WIDTH,
					  LIST_CURSOR_HEIGHT + LIST_CURSOR_HEIGHT_REST,
					  FOREGROUND);

		if(IsKeyDown(KEY_DOWN) && tick - touch_tick_start >= KEY_DELAY)
		{
			touch_tick_start = tick;
			selected_item = (selected_item + 1) % ITEMS_COUNT;
			offset_item = selected_item / LIST_MAX_ITEMS;

			printf(
				"[%lu] PRESS DW: offset_list_item [%d], selected_list_item "
				"[%d]\n",
				tick,
				offset_item,
				selected_item);
		}
		if(IsKeyDown(KEY_UP) && tick - touch_tick_start >= KEY_DELAY)
		{
			touch_tick_start = tick;

			if(selected_item == 0) selected_item = ITEMS_COUNT;
			selected_item--;
			offset_item = selected_item / LIST_MAX_ITEMS;

			printf(
				"[%lu] PRESS UP: offset_list_item [%d], selected_list_item "
				"[%d]\n",
				tick,
				offset_item,
				selected_item);
		}

		for(i = LIST_MAX_ITEMS * offset_item;
			i < ITEMS_COUNT && i < LIST_MAX_ITEMS * (offset_item + 1);
			++i)
		{
			const n16 LIST_ITEM_REL_Y =
				LIST_REL_Y
				+ (i - LIST_MAX_ITEMS * offset_item)
					  * (LIST_ITEM_HEIGHT + LIST_ITEM_MARGIN);

			ListItem item = ITEMS[i];

			if(i == selected_item)
			{
				DrawRectangle(LIST_REL_X,
							  LIST_ITEM_REL_Y,
							  LIST_ITEM_MAX_WIDTH,
							  LIST_ITEM_HEIGHT + LIST_ITEM_HEIGHT_REST
								  + LIST_ITEM_MARGIN,
							  FOREGROUND);
			}

			DrawText(item.text,
					 LIST_REL_X + PADDING,
					 LIST_ITEM_REL_Y
						 + (LIST_ITEM_MARGIN + LIST_ITEM_HEIGHT_REST) / 2
						 + LIST_ITEM_FONT_SIZE / 4,
					 LIST_ITEM_FONT_SIZE,
					 (i == selected_item) ? BACKGROUND : FOREGROUND);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
#endif
