#include "maze.h"

#define PLANE_W 320
#define PLANE_H 200
#define DIST_TO_PLANE 277
#define SLICE_W 5
#define ANGLE_INC 1

Vector *cast_ray(Maze this, Vector *arr,  int dof, float dis, float Tan);

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

	ra = fix_ang(player->ang + 30);
	for (r = 0; r <= 60; r++)
	{
		/** ---Vertical--- **/

		Tan = tan(deg_to_rad(ra));
		vecY = y_rays(player, map, ra, Tan, math);
		vx = vecY->x;
		vy = vecY->y;

		/** ---Horizontal--- **/
		vecX = x_rays(player, map, ra, Tan, math);

		/** dark shade **/
		SDL_SetRenderDrawColor(win->renderer, 125, 125, 125, 255);
		if (vecY->dist < vecX->dist)
		{
			rx = vx;
			ry = vy;
			vecX->dist = vecY->dist;
			/** light shade **/
			SDL_SetRenderDrawColor(win->renderer, 105, 105, 105, 255);
		}

		/**draw_line(win, player->x, player->y, rx, ry);**/

		vecX->dist *= cos(deg_to_rad(ra - player->ang));
		slice = ((map->gridS << 1) / vecX->dist) * DIST_TO_PLANE;

		slice /= 2;

		if (slice > PLANE_H)
			slice = PLANE_H;

		draw_rect(win, (r * SLICE_W), (PLANE_H - slice) / 2, SLICE_W, slice);

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
	int dof;
	Vector *vec;
	Maze this;

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
		dof = map->DOF;
	}

	this.player = player;
	this.map = map;
	this.math = math;
	Vector arr[] = {{rx, ry, ra}, {xo, yo, 0.0}};

	vec = cast_ray(this, arr, dof, disV, Tan);
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
	int dof;
	Vector *vec;
	Maze this;

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
		dof = map->DOF;
	}

	this.player = player;
	this.map = map;
	this.math = math;
	Vector arr[] = {{rx, ry, ra}, {xo, yo, 0.0}};

	vec = cast_ray(this, arr, dof, disH, Tan);
	return (vec);
}

/**
 * cast_ray - spits out ray until wall hit
 *
 * @this: Input, player, map and math variables
 * @arr: Input, ray and offset coordinates
 * @dis: Input, distance
 * @Tan: Input, tangent
 *
 * Return: Vector (ray: x&y, distance)
 **/
Vector *cast_ray(Maze this, Vector *arr,  int dof, float dis, float Tan)
{
	int mx, my, mp, dov, gridX, gridY;
	float ra, rx, ry, px, py, xo, yo, dist_rpx, dist_rpy;
	Vector *vec;

	ra = arr[0].dist;
	rx = arr[0].x;
	ry = arr[0].y;

	xo = arr[1].x;
	yo = arr[1].y;

	px = this.player->x;
	py = this.player->y;

	dov = this.map->DOF;

	while (dof < dov)
	{
		mx = (int)(rx) >> 6;
		my = (int)(ry) >> 6;
		mp = my * this.map->gridX + mx;

		gridX = this.map->gridX;
		gridY = this.map->gridY;
		if (mp > 0 && mp < gridX * gridY && this.map->grid[mp] == 1)
		{
			dof = dov;
			dist_rpx = this.math->cos_lookup[(int)ra % 360] * (rx - px);
			dist_rpy = this.math->sin_lookup[(int)ra % 360] * (ry - py);

			dis = dist_rpx - dist_rpy;
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
	vec->dist = dis;
	return (vec);
}
