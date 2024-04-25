#include "components.h"
#include "graphics.h"

void ListView(n16 posX,
			  n16 posY,
			  n16 width,
			  n16 height,
			  const ListItem *items,
			  n64 items_count,
			  n64 *selected,
			  Color foreground,
			  Color background)
{
	n64 i, offset_item = 0;

	const n16 BAR_WIDTH = 15;

	const n16 ITEM_MARGIN = 8;
	const n16 ITEM_FONT_SIZE = 20;
	const n16 ITEM_WIDTH = width - BAR_WIDTH - PADDING;
	const n16 ITEM_HEIGHT = 24;
	const n16 MAX_ITEMS = height / (ITEM_HEIGHT + ITEM_MARGIN);

	const n16 BAR_HEIGHT = (ITEM_HEIGHT + ITEM_MARGIN) * MAX_ITEMS;
	const n16 BAR_REL_X = width - BAR_WIDTH + PADDING;
	const n16 BAR_REL_Y = posY;

	const n16 CURSOR_HEIGHT = (BAR_HEIGHT / items_count);
	const n16 CURSOR_HEIGHT_REST = (BAR_HEIGHT % items_count);

	GFX_draw_rect(
		BAR_REL_X, BAR_REL_Y, BAR_WIDTH, BAR_HEIGHT, STROKE, foreground);

	GFX_draw_rect_fill(BAR_REL_X,
					   BAR_REL_Y + (*selected) * CURSOR_HEIGHT,
					   BAR_WIDTH,
					   CURSOR_HEIGHT + CURSOR_HEIGHT_REST,
					   foreground);

	offset_item = *selected / MAX_ITEMS;

	for(i = MAX_ITEMS * offset_item;
		i < items_count && i < MAX_ITEMS * (offset_item + 1);
		++i)
	{
		const n16 ITEM_REL_Y =
			posY + (i - MAX_ITEMS * offset_item) * (ITEM_HEIGHT + ITEM_MARGIN);

		ListItem item = items[i];

		if(i == *selected)
		{
			GFX_draw_rect_fill(posX,
							   ITEM_REL_Y,
							   ITEM_WIDTH,
							   ITEM_HEIGHT + ITEM_MARGIN,
							   foreground);

			/* Draw Bezel */
#define BEZEL_CENTER              \
	posX + ITEM_WIDTH - HPADDING, \
		(n64)(ITEM_REL_Y + (ITEM_HEIGHT + ITEM_MARGIN) / 2)

			GFX_draw_line(posX + ITEM_WIDTH - PADDING,
						  ITEM_REL_Y + (ITEM_HEIGHT + ITEM_MARGIN) / 4,
						  BEZEL_CENTER,
						  STROKE + 1,
						  background);

			GFX_draw_line(BEZEL_CENTER,
						  posX + ITEM_WIDTH - PADDING,
						  ITEM_REL_Y + (ITEM_HEIGHT + ITEM_MARGIN) * 3 / 4,
						  STROKE + 1,
						  background);
		}

		GFX_draw_text(item.text,
					  posX + PADDING,
					  ITEM_REL_Y + ITEM_MARGIN / 2 + ITEM_FONT_SIZE / 4,
					  ITEM_FONT_SIZE,
					  (i == *selected) ? background : foreground);
	}
}
