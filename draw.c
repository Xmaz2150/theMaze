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

	/*center_x = player->x + 5;
	center_y = player->y + 5;
	SDL_SetRenderDrawColor(win->renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(win->renderer,
						 center_x,
						 center_y, 
						 center_x + player->dx * 50,
						 center_y + player->dy * 50);*/
	//draw_rect(win, player->x -5, player->y-5, 10, 10);
	draw_ray(win, player, map, math);
	//ray_cast(win, player, map, math);
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
