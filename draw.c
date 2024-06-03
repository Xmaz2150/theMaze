#include "maze.h"

/**
 * draw_stuff - draws graphics to window
 * @win: Input, window
 * @this: Input- player, grid & math
 **/
void draw_stuff(SDL_Instance *win, Maze *this)
{
	MAZE

	SDL_SetRenderDrawColor(win->renderer, 0, 0, 125, 255);
	draw_rect(win, 0, 0, 305, 100);
	SDL_SetRenderDrawColor(win->renderer, 0, 125, 0, 255);
	draw_rect(win, 0, 100, 305, 100);
	draw_ray(win, this);

	if (map->draw)
	{
		draw_grid(win, map);
		SDL_SetRenderDrawColor(win->renderer, 255, 0, 0, 255);
		draw_rect(win, player->x / 10 + 5, player->y / 10 + 5, 5, 5);
	}
}

/**
 * ray_cast - ray caster
 * @win: Input, window
 * @player: Input, player
 * @map: Input, map
 * @math: Input, sin and cos lookups
 **/
void ray_cast(SDL_Instance *win, Player *player, Grid *map, Math *math)
{
	float Ax, Ay, tAx, tAy, Ya, Xa, a_rad;

	a_rad = deg_to_rad(player->ang);
	/**
	 * //horizontal lines
	 * Ya = 64
	 * Xa = 64/tan(a)
	 *
	 * if r is facing up
	 * 	A.y = ((P.y/64) * 64) - 1
	 *
	 * else
	 * 	A.y = ((P.y/64) * 64) + 64
	 *
	 * A.x = P.x + (P.y - A.y)/tan(a)
	 *
	 * next points:
	 *
	 * N.x = A.x + Xa
	 * N.y = A.y + Ya
	 *
	 **/
	Ya = 64;
	Xa = 64/tan(a_rad);
	if (a_rad < M_PI || a_rad > 0)
	{
		Ay = ((int) (player->y/64) * 64) - 1;
		Ya *= -1;
	}
	else if (a_rad > M_PI)
	{
		Ay = ((int) (player->y/64) * 64) + 64;
		Xa *= -1;
	}
	Ax = player->x + (player->y - Ay)/tan(a_rad);
	
	float Cx = Ax + Xa;
	float Cy = Ay + Ya;
	printf("A(%f, %f)\nC(%f, %f)\n", Ax/64, Ay/64, Cx/64, Cy/64);

	/**
	 * //vertical lines
	 *
	 * Ya = 64*tan(a)
	 * Xa = 64
	 *
	 * if r is facing right
	 * 	B.x = ((P.x/64) * 64) + 64
	 *
	 * else
	 * 	B.x = ((P.x/64) * 64) - 1
	 *
	 * B.y = P.y + (P.x - B.x)*tan(a)
	 *
	 * next points:
	 *
	 *
	 * E.x = B.x + Xa
	 * E.y = B.y + Ya
	 *
	 **/
	/*Ya = 64*tan(a_rad);
	Xa = 64;
	if (a_rad < M_PI/2 || a_rad > (M_PI + M_PI/2))
	{
		Ax = ((int) (player->x/64) * 64) + 64;
		Ya *= -1;
	}
	else if (a_rad > M_PI/2 && a_rad < (M_PI + M_PI/2))
	{
		Ax = ((int) (player->x/64) * 64) - 1;
		Xa *= -1;
	}
	Ay = player->y + (player->x - Ax)*tan(a_rad);

	float Ex = Ax + Xa;
	float Ey = Ay + Ya;
	printf("\nB(%f, %f)\nE(%f, %f)\n", Ax/64, Ay/64, Ex/64, Ey/64);*/
	/**
	 * dist P->D = sqrt((P.x - D.x)^2 + (P.y - D.y)^2)
	 **/
	/* or */
	/**
	 * dist p->D = ABS(P.x - D.x)/cos(a) = ABS(P.y - D.y)/sin(a)
	 **/
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
