#include "maze.h"

/**
 * draw_stuff - draws graphics to window
 * @win: Input, window
 * @player: Input, player
 **/
void draw_stuff(SDL_Instance *win, Player *player)
{
	(void) win;
	(void) player;
}

/**
 * draw_rect - draws rectangle to screen provided color is already set
 * @win: Input, window
 * @beginX: Input, starting point along x axis
 * @beginY: Input, starting point along y axis
 * @w: Input, rectangle width
 * @h: Input, rectangle height
 **/
void draw_rect(SDL_Instance *win, int beginX, int beginY, int w, int h)
{
	SDL_Rect fillRect = {beginX, beginY, w, h};

	SDL_RenderFillRect(win->renderer, &fillRect);
}
