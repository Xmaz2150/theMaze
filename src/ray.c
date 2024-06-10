#include "../inc/maze.h"
#include "../inc/textures.h"

void s_texture(SDL_Instance *win, float slice, float shade, Vector ray, float r, int mapt);

/**
 * draw_ray - casts rays
 * @win: Input, window
 * @this: Input- player, grid & math
 **/

void draw_ray(SDL_Instance *win, Maze *this)
{
	float vx, vy, rx, ry, ra, r, Tan, slice, shade;
	Vector vecX, vecY;

	MAZE
	(void)rx;
	(void)ry;
	ra = fix_ang(player->ang + 30);
	for (r = 0; r <= 60; r++)
	{
		int vmt=0, hmt=0; //vertical and horizontal map trxture #
		Tan = tan(deg_to_rad(ra));

		vecY = vertical_lines(this, ra, Tan, &vmt);
		vx = vecY.x;
		vy = vecY.y;
		vecX = horizontal_lines(this, ra, Tan, &hmt);
		/** dark shade **/
		SDL_SetRenderDrawColor(win->renderer, 125, 125, 125, 255);
		shade = 1;

		if (vecY.dist < vecX.dist)
		{
			hmt=vmt;
			rx = vx;
			ry = vy;
			vecX.dist = vecY.dist;
			/** lighter shade **/
			SDL_SetRenderDrawColor(win->renderer, 105, 105, 105, 255);
			shade = 0.5;
		}
		else
		{
			rx = vecX.x;
			ry = vecX.y;
		}
		if (map->draw == true)
			draw_l(win,
			player->x / 10 + (P_W + 20),
			player->y / 10,
			rx / 10 + (P_W + 20), ry / 10);

		vecX.dist *= cos(deg_to_rad(ra - player->ang));
		slice = ((map->gridS << 1) / vecX.dist) * DIST_TO_PLANE;
		slice /= 2;

		Vector ray = {rx, ry, ra};

		s_texture(win, slice, shade, ray, r, hmt);

		ra = fix_ang(ra - ANGLE_INC);
	}
}

void s_texture(SDL_Instance *win, float slice, float shade, Vector ray, float r, int mapt)
{
	float tx, ty, ty_off, ty_step;
	float ra, rx, ry;
	int y;

	ra = ray.dist;
	rx = ray.x;
	ry = ray.y;

	ty_step = 32.0 / (float)slice;
	ty_off = 0;
	if (slice > PLANE_H)
	{
		ty_off = (slice - PLANE_H) / 2.0;
		slice = PLANE_H;
	}
	ty = ty_off * ty_step + mapt*32;
	if (shade == 1)
	{
		tx = (int)(rx / 2.0) % 32;
		if (ra > 180)
			tx = 31 - tx;
	}
	else
	{
		/**
		* tx = (int)(ry / 2.0) % 32; if (ra > 90 && ra < 270) {tx = 31 - tx;}
		* **/
		tx = (int)(ry / 2.0) % 32;
		if (ra > 180)
			tx = 31 - tx;
	}

	ty += 32*2;
	for (y = 0; y < slice; y++)
	{
		float c = (All_Textures[(int)(ty) * 32 + (int) (tx)] * shade) * 255;

		SDL_SetRenderDrawColor(win->renderer, c, c, c, 255);
		draw_rect(win, (r * SLICE_W), ((PLANE_H - slice) / 2) + y, SLICE_W, SLICE_W);
		ty += ty_step;
	}
}
/**
 * vertical_lines - casts rays along y axis
 * @this: Input- player, grid & math
 * @ra: Input, current ray angle
 * @Tan: Input, tangent
 *
 * Return: Vector
 **/
Vector vertical_lines(Maze *this, float ra, float Tan, int *vmt)
{
	float rx, ry, xo, yo, disV;
	int dof;
	Vector vec;

	MAZE

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
	Vector arr[] = {{rx, ry, ra}, {xo, yo, 0.0}};

	vec = cast_ray(this, arr, dof, disV, vmt);
	return (vec);

}

/**
 * horizontal_lines - casts rays along x axis
 * @this: Input- player, grid & math
 * @ra: Input, current ray angle
 * @Tan: Input, tangent
 *
 * Return: Vector
 **/
Vector horizontal_lines(Maze *this, float ra, float Tan, int *hmt)
{
	float rx, ry, xo, yo, disH;
	int dof;
	Vector vec;

	MAZE

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

	Vector arr[] = {{rx, ry, ra}, {xo, yo, 0.0}};

	vec = cast_ray(this, arr, dof, disH, hmt);
	return (vec);
}

/**
 * cast_ray - spits out ray until wall hit
 *
 * @this: Input, player, map and math variables
 * @arr: Input, ray and offset coordinates
 * @dof: Input, depth of field
 * @dis: Input, distance
 *
 * Return: Vector (ray: x&y, distance)
 **/
Vector cast_ray(Maze *this, Vector *arr,  int dof, float dis, int *mapt)
{
	int mx, my, mp, gridX, gridY;
	float ra, rx, ry, xo, yo, dist_rpx, dist_rpy;
	Vector vec;

	MAZE
	ra = arr[0].dist;
	rx = arr[0].x;
	ry = arr[0].y;
	xo = arr[1].x;
	yo = arr[1].y;

	while (dof < map->DOF)
	{
		mx = (int)(rx) >> 6;
		my = (int)(ry) >> 6;
		mp = my * map->gridX + mx;
		gridX = map->gridX;
		gridY = map->gridY;
		if (mp > 0 && mp < gridX * gridY && map->grid[mp] > 0)
		{
			*mapt = map->grid[mp] - 1;
			dof = map->DOF;
			dist_rpx = math->cos_lookup[(int)ra % 360] * (rx - player->x);
			dist_rpy = math->sin_lookup[(int)ra % 360] * (ry - player->y);
			dis = dist_rpx - dist_rpy;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	vec.x = rx;
	vec.y = ry;
	vec.dist = dis;
	return (vec);
}
