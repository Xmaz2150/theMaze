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
	float end_x, end_y, i;
	int center_x, center_y, radius;

	draw_ray(win, player, map, math);

	draw_grid(win, map);
	SDL_SetRenderDrawColor(win->renderer, 255, 0, 0, 255);
	draw_rect(win, player->x / 10 + 5, player->y / 10 + 5, 5, 5);
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

/**
 * draw_grid - draws grid
 * @win: Input, window
 * @map: Input, map
 **/
void draw_grid(SDL_Instance *win, Grid *map)
{
	int x, y, xo, yo, idx, gridS;

	gridS = 10;
	for (y = 0; y < map->gridY; y++)
	{
		for (x = 0; x < map->gridX; x++)
		{
			idx = y * map->gridX + x;

			xo = x * gridS;
			yo = y * gridS;
			SDL_Rect fillRect = {xo, yo, gridS - 1, gridS - 1};

			if (map->grid[idx] == 1)
				SDL_SetRenderDrawColor(win->renderer, 255, 255, 0, 255);
			else
				SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(win->renderer, &fillRect);
		}
	}
}
