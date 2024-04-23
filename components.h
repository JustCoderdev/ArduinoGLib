#ifndef COMPONENTS_
#define COMPONENTS_

#include "./graphics.h"

typedef struct {
	char *text;
	n8 text_len;
} ListItem;

void ListView(n16 posX,
			  n16 posY,
			  n16 width,
			  n16 height,
			  const ListItem *items,
			  n64 items_count,
			  n64 *selected,
			  Color foreground,
			  Color background);

#endif  /* COMPONENTS_ */
