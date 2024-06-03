#include "../inc/maze.h"

/**
 * key_events - listens to key presses
 * @this: Input- player, grid & math
 *
 * Return: (0) Success
 **/
int key_events(Maze *this)
{
	MAZE
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				key = event.key;
				if (key.keysym.sym == SDLK_ESCAPE)
					return (1);
				if (key.keysym.sym == SDLK_LEFT)
				{
					player->ang = fix_ang(player->ang + 5);
					player->dx = math->cos_lookup[(int)player->ang % 360];
					player->dy = -math->sin_lookup[(int)player->ang % 360];
				}
				if (key.keysym.sym == SDLK_RIGHT)
				{
					player->ang = fix_ang(player->ang - 5);
					player->dx = math->cos_lookup[(int)player->ang % 360];
					player->dy = -math->sin_lookup[(int)player->ang % 360];
				}
				if (key.keysym.sym == SDLK_UP)
					update_pos(this, player->dx * 5, player->dy * 5, 'u');

				if (key.keysym.sym == SDLK_DOWN)
					update_pos(this, player->dx * 5, player->dy * 5, 'd');

				if (key.keysym.sym == SDLK_g)
					map->draw = !map->draw;
				break;
		}
	}
	return (0);
}

/**
 * update_pos - moves player forward & backward and checks collisions
 * @this: Input- player, grid & math
 * @dx: Input, delta X
 * @dy: Input, delta Y
 * @flag: Input, checks for direction
 *
 **/
void update_pos(Maze *this, float dx, float dy, char flag)
{
	int xo, yo, ipx, ipy, ipx_add_xo, ipy_add_yo, ipx_sub_xo, ipy_sub_yo, margin;

	MAZE

	margin = 20;
	xo = 0;
	yo = 0;

	if (player->dx < 0)
		xo = -margin;
	else
		xo = margin;

	if (player->dy < 0)
		yo = -margin;
	else
		yo = margin;

	ipx = player->x / map->gridS;
	ipx_add_xo = (player->x + xo) / map->gridS;
	ipx_sub_xo = (player->x - xo) / map->gridS;

	ipy = player->y / map->gridS;
	ipy_add_yo = (player->y + yo) / map->gridS;
	ipy_sub_yo = (player->y - yo) / map->gridS;

	if (flag == 'u')
	{
		if (map->grid[ipy * map->gridX + ipx_add_xo] == 0)
			player->x += dx;
		if (map->grid[ipy_add_yo * map->gridX + ipx] == 0)
			player->y += dy;
	}
	else if (flag == 'd')
	{
		if (map->grid[ipy * map->gridX + ipx_sub_xo] == 0)
			player->x -= dx;
		if (map->grid[ipy_sub_yo * map->gridX + ipx] == 0)
			player->y -= dy;
	}
}
