#include "./components.h"

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

	const n16 LIST_BAR_WIDTH = 15;
	const n16 LIST_BAR_HEIGHT = height;
	const n16 LIST_BAR_REL_X = width - LIST_BAR_WIDTH + PADDING;
	const n16 LIST_BAR_REL_Y = posY;

	const n16 LIST_CURSOR_HEIGHT = (LIST_BAR_HEIGHT / items_count);
	const n16 LIST_CURSOR_HEIGHT_REST = (LIST_BAR_HEIGHT % items_count);

	const n16 LIST_ITEM_MARGIN = 8;
	const n16 LIST_ITEM_FONT_SIZE = 20;
	const n16 LIST_ITEM_WIDTH = width - LIST_BAR_WIDTH - PADDING;
	const n16 LIST_ITEM_HEIGHT = 25;
	const n16 LIST_MAX_ITEMS = height / (LIST_ITEM_HEIGHT + LIST_ITEM_MARGIN);
	/* const n16 LIST_ITEM_HEIGHT_REST = */
	/* 	height - (LIST_ITEM_HEIGHT + LIST_ITEM_MARGIN) * LIST_MAX_ITEMS; */

	Rectangle LIST_BAR_BORDER = {0};
	LIST_BAR_BORDER.x = LIST_BAR_REL_X;
	LIST_BAR_BORDER.y = LIST_BAR_REL_Y;
	LIST_BAR_BORDER.width = LIST_BAR_WIDTH;
	LIST_BAR_BORDER.height = LIST_BAR_HEIGHT;

	DrawRectangleLinesEx(LIST_BAR_BORDER, STROKE, foreground);
	DrawRectangle(LIST_BAR_REL_X,
				  LIST_BAR_REL_Y + (*selected) * LIST_CURSOR_HEIGHT,
				  LIST_BAR_WIDTH,
				  LIST_CURSOR_HEIGHT + LIST_CURSOR_HEIGHT_REST,
				  foreground);

	offset_item = *selected / LIST_MAX_ITEMS;

	for(i = LIST_MAX_ITEMS * offset_item;
		i < items_count && i < LIST_MAX_ITEMS * (offset_item + 1);
		++i)
	{
		const n16 LIST_ITEM_REL_Y =
			posY
			+ (i - LIST_MAX_ITEMS * offset_item)
				  * (LIST_ITEM_HEIGHT + LIST_ITEM_MARGIN);

		ListItem item = items[i];

		if(i == *selected)
		{
			DrawRectangle(posX,
						  LIST_ITEM_REL_Y,
						  LIST_ITEM_WIDTH,
						  LIST_ITEM_HEIGHT + LIST_ITEM_MARGIN,
						  foreground);
		}

		DrawText(item.text,
				 posX + PADDING,
				 LIST_ITEM_REL_Y
					 + LIST_ITEM_MARGIN / 2
					 + LIST_ITEM_FONT_SIZE / 4,
				 LIST_ITEM_FONT_SIZE,
				 (i == *selected) ? background : foreground);
	}
}
