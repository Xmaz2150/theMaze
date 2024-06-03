#include "maze.h"

/**
 * draw_stuff - draws graphics to window
 * @win: Input, window
 * @player: Input, player
 * @map: Input, map
 * @math: Input, sin and cos lookups
 **/
void draw_stuff(SDL_Instance *win, Player *player, Grid *map, Math *math)
{
	draw_ray(win, player, map, math);
}

/**
 * draw_rect - draws rectplayer->ang to screen provided color is already set
 * @win: Input, window
 * @beginX: Input, starting point along x axis
 * @beginY: Input, starting point along y axis
 * @w: Input, rectplayer->ang width
 * @h: Input, rectplayer->ang height
 **/
void draw_rect(SDL_Instance *win, int beginX, int beginY, int w, int h)
{
	SDL_Rect fillRect = {beginX, beginY, w, h};

	SDL_RenderFillRect(win->renderer, &fillRect);
}

/**
 * draw_line - draws line to screen provided color is already set
 * @win: Input, window
 * @beginX: Input, starting point along x axis
 * @beginY: Input, starting point along y axis
 * @endX: Input, last point along x axis
 * @endY: Input, last point along y axis
 **/
void draw_line(SDL_Instance *win, int beginX, int beginY, int endX, int endY)
{
	SDL_RenderDrawLine(win->renderer,
		     beginX,
		     beginY,
		     endX,
		     endY
	);
}
