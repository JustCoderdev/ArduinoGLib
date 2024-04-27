#include "components.h"
#include "graphics.h"

void LoadingBar(n16 posX, n16 posY, n16 width, n16 height, n64 current_progress,
                n64 total_progress, Color foreground, Color background)
{
	float progress_perc = ((float)current_progress) / total_progress;

	GFX_draw_round_rect(posX, posY, width, height, STROKE, 15, foreground);
	GFX_draw_round_rect_fill(
	    posX, posY, width * progress_perc, height, 20, foreground);
}
