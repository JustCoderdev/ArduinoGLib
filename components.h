#ifndef COMPONENTS_
#define COMPONENTS_

#include "./lib/raylib.h"

/* Types */
typedef unsigned char n8;
typedef unsigned short n16;
typedef unsigned int n32;
typedef unsigned long int n64;

/* Controls */
#define KEY_DELAY 1500
#define KEY_UP ((int)'K')
#define KEY_DOWN ((int)'J')
#define KEY_LEFT ((int)'H')
#define KEY_RIGHT ((int)'L')
#define KEY_OK KEY_ENTER

/* Colors */
extern const Color BLACK;
extern const Color GRAY;
extern const Color WHITE;

extern const Color DEBUG_GRAY;

extern const Color TINT_RED;
extern const Color TINT_PINK;
extern const Color TINT_GREEN;
extern const Color TINT_BLUE;

#define PADDING 10
#define DPADDING (2 * PADDING)

#define STROKE 2
#define DSTROKE (2 * STROKE)

/* ListView */
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
