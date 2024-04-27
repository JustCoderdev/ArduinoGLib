#ifndef GFX_COMPONENTS_H_
#define GFX_COMPONENTS_H_

#include "graphics.h"

typedef struct {
	char *text;
	n64   text_len;
} ListItem;

void ListView(n16 posX, n16 posY, n16 width, n16 height, const ListItem *items,
              n64 items_count, n64 *selected, Color foreground,
              Color background);

void LoadingBar(n16 posX, n16 posY, n16 width, n16 height, n64 current_progress,
                n64 total_progress, Color foreground, Color background);

#endif /* GFX_COMPONENTS_H_ */
