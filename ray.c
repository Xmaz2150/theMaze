#include "maze.h"

#define PLANE_W 320
#define PLANE_H 200
#define DIST_TO_PLANE 277
#define SLICE_W 10
#define ANGLE_INC 1
/**
 * draw_ray - casts rays
 * @win: Input, window
 * @player: Input, player
 * @map: Input, grid
 * @math: Input, sin and cos lookups
 **/

void draw_ray(SDL_Instance *win, Player *player, Grid *map, Math *math)
{
	float vx, vy, rx, ry, ra, r, Tan, slice;
	Vector *vecX, *vecY;

	ra = fix_ang(player->ang + 35);
	for (r = 0; r < 72; r++)
	{
		/** ---Vertical--- **/

		Tan = tan(deg_to_rad(ra));
		vecY = y_rays(player, map, ra, Tan, math);
		vx = vecY->x;
		vy = vecY->y;

		/** ---Horizontal--- **/
		vecX = x_rays(player, map, ra, Tan, math);

		/**dark shade**/
		SDL_SetRenderDrawColor(win->renderer, 125, 125, 125, 255);
		if (vecY->dist < vecX->dist)
		{
			rx = vx;
			ry = vy;
			vecX->dist = vecY->dist;
			/**light shade**/
			SDL_SetRenderDrawColor(win->renderer, 105, 105, 105, 255);
		}

		/**draw_line(win, player->x, player->y, rx, ry);**/

		vecX->dist *= cos(deg_to_rad(ra - player->ang));
		slice = ((map->gridS << 1) / vecX->dist) * DIST_TO_PLANE;
		draw_rect(win, (r * SLICE_W), (PLANE_H / 2) - (slice / 2), SLICE_W, slice);

		ra = fix_ang(ra - ANGLE_INC);
	}
}
/**
 * y_rays - casts rays along y axis
 * @player: Input, player
 * @map: Input, grid
 * @ra: Input, current ray angle
 * @Tan: Input, tangent
 * @math: Input, sin and cos lookups
 *
 * Return: Vector
 **/
Vector *y_rays(Player *player, Grid *map, float ra, float Tan, Math *math)
{
	float rx, ry, xo, yo, disV;
	int mx, my, mp, dof;
	Vector *vec;

	dof = 0;
	disV = 100000;
	if (math->cos_lookup[(int)ra % 360] > 0.001)
	{
		rx = (((int)player->x >> 6) << 6) + 64;
		ry = (player->x - rx) * Tan + player->y;
		xo = 64;
		yo = -xo * Tan;
	}
	else if (math->cos_lookup[(int)ra % 360] < -0.001)
	{
		rx = (((int)player->x >> 6) << 6) - 0.0001;
		ry = (player->x - rx) * Tan + player->y;
		xo = -64;
		yo = -xo * Tan;
	}
	else
	{
		rx = player->x;
		ry = player->y;
		dof = 8;
	}

	while (dof < 8)
	{
		mx = (int)(rx) >> 6;
		my = (int)(ry) >> 6;
		mp = my * map->gridX + mx;
		if (mp > 0 && mp < map->gridX * map->gridY && map->grid[mp] == 1)
		{
			dof = 8;
			disV = math->cos_lookup[(int)ra % 360] * (rx - player->x) - math->sin_lookup[(int)ra % 360] * (ry - player->y);
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}

	vec = malloc(sizeof(Vector));
	if (vec == NULL)
		return (NULL);

	vec->x = rx;
	vec->y = ry;
	vec->dist = disV;
	return (vec);

}

/**
 * x_rays - casts rays along x axis
 * @player: Input, player
 * @map: Input, grid
 * @ra: Input, current ray angle
 * @Tan: Input, tangent
 * @math: Input, sin and cos lookups
 *
 * Return: Vector
 **/
Vector *x_rays(Player *player, Grid *map, float ra, float Tan, Math *math)
{
	float rx, ry, xo, yo, disH;
	int mx, my, mp, dof;
	Vector *vec;

	dof = 0;
	disH = 100000;
	Tan = 1.0 / Tan;
	if (math->sin_lookup[(int)ra % 360] > 0.001)
	{
		ry = (((int)player->y >> 6) << 6) - 0.0001;
		rx = (player->y - ry) * Tan + player->x;
		yo = -64;
		xo = -yo * Tan;
	}
	else if
	(math->sin_lookup[(int)ra % 360] < -0.001)
	{
		ry = (((int)player->y >> 6) << 6) + 64;
		rx = (player->y - ry) * Tan + player->x;
		yo = 64;
		xo = -yo * Tan;
	}
	else
	{
		rx = player->x;
		ry = player->y;
		dof = 8;
	}

	while (dof < 8)
	{
		mx = (int)(rx) >> 6;
		my = (int)(ry) >> 6;
		mp = my * map->gridX + mx;
		if (mp > 0 && mp < map->gridX * map->gridY && map->grid[mp] == 1)
		{
			dof = 8;
			disH = math->cos_lookup[(int)ra % 360] * (rx - player->x) - math->sin_lookup[(int)ra % 360] * (ry - player->y);
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}

	vec = malloc(sizeof(Vector));
	if (vec == NULL)
		return (NULL);

	vec->x = rx;
	vec->y = ry;
	vec->dist = disH;
	return (vec);
}
