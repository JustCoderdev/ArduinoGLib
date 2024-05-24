#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"

typedef void (*StateIntCallback)(int oldVal, int newVal);
typedef struct {
	StateIntCallback callback;
	int              value;
} StateInt;

/* Initializer */
StateInt *state_init(int initialValue)
{
	StateInt *state = malloc(sizeof(*state));
	state->value = initialValue;
	return state;
}

/* StateIntCallback generate_callback(int value) { */

/* } */

void state_free(StateInt *state)
{
	free(state);
}

/* Getters and Setters */
int state_get(StateInt *state)
{
	return state->value;
}

bool state_updated(StateInt *state, int value)
{
	return state->value != value;
}

int state_set(StateInt *state, int value)
{
	if(state->callback != NULL) state->callback(state->value, value);

	return state->value = value;
}

void state_assign(StateInt *state, StateIntCallback callback)
{
	state->callback = callback;
}

void callback(int oldVal, int newVal)
{
	printf("State: old %d, new %d\n", oldVal, newVal);
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

#define TICK_MAX_LEN (20 + 1)
void drawScreen(Color foreground, Color background, n64 *tick, char *text,
                StateInt *state)
{
	GFX_draw_rect(0, 0, WIDTH, HEIGHT, STROKE, foreground);

	tick_to_string(++(*tick), text, TICK_MAX_LEN);
	GFX_draw_text(text, 2, 2, 6, DEBUG_GRAY, background);

	tick_to_string(state_get(state), text, TICK_MAX_LEN);
	GFX_draw_text(text, 15, 20, 6, foreground, background);
}

int main(void)
{
#ifdef DEB_STATETEST
	/* StateInt* state = state_init(15); */
	/* state_assign(state, callback); */

	/* printf("State: %d\n", state_get(state)); */

	/* state_set(state, 25); */
	/* printf("State: %d\n", state_get(state)); */

	/* state_free(state); */
#endif

	StateInt *state = state_init(0);
	n64       tick = 0;
	int       old_state = -1;

	Color background = GRAY;
	Color foreground = TINT_RED;

	char text[TICK_MAX_LEN];
	text[TICK_MAX_LEN - 1] = '\0';

	/* state_assign(state, StateIntCallback callback); */

	GFX_window_initialise();
	while(!GFX_window_should_close())
	{
		/* Handle inputs */
		if(GFX_input_key_is_down(KEY_OK))
			state_set(state, state_get(state) + 1);

		if(!state_updated(state, old_state)) continue;

		GFX_screen_begin();
		GFX_screen_fill(background);

		drawScreen(foreground, background, &tick, text, state);
		old_state = state_get(state);

		GFX_screen_switch();
	}

	GFX_window_finalise();
	state_free(state);

	return 0;
}
