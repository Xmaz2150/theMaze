#include "maze.h"

/**
 * collide_f - moves player forward and checks collisions
 * @player: Input, player
 * @map: Input, map
 * @dx: Input, delta X
 * @dy: Input, delta Y
 *
 * Return: (0) Success
 **/
void collide_f(Player **player, Grid *map, float dx, float dy)
{
	int xo, yo, ipx, ipy, ipx_add_xo, ipy_add_yo, margin;

	margin = 20;

	xo = 0;
	yo = 0;

	if ((*player)->dx < 0)
		xo = -margin;
	else
		xo = margin;

	if ((*player)->dy < 0)
		yo = -margin;
	else
		yo = margin;

	ipx = (*player)->x / map->gridS;
	ipx_add_xo = ((*player)->x + xo) / map->gridS;

	ipy = (*player)->y / map->gridS;
	ipy_add_yo = ((*player)->y + yo) / map->gridS;

	if (map->grid[ipy * map->gridX + ipx_add_xo] == 0)
		(*player)->x += dx;
	if (map->grid[ipy_add_yo * map->gridX + ipx] == 0)
		(*player)->y += dy;
}

/**
 * key_events - listens to key presses
 * @player: Input, player
 * @math: Input, lookup tables
 * @map: Input, map
 *
 * Return: (0) Success
 **/
int key_events(Player *player, Math *math, Grid *map)
{
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
					collide_f(&player, map, player->dx * 5, player->dy * 5);

				if (key.keysym.sym == SDLK_DOWN)
				{
					player->x -= player->dx * 5;
					player->y -= player->dy * 5;
				}
				if (key.keysym.sym == SDLK_g)
					map->draw = !map->draw;

				break;
		}
	}
	return (0);
}
