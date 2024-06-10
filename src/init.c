#include "../inc/maze.h"

int grid[] = {
	1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

/**
 * m_init - initializes integral types
 * @maze: Input- player, grid & math
 * Return: (0) Success
 **/
int m_init(Maze *maze)
{
	if (init_player(maze->player) == 1 || init_map(maze->map) == 1)
		return (1);
	precompute_lookup_tables(maze->math);
	return (0);
}

/**
 * init_player - initializes player
 * @player: Input, player
 *
 * Return: (0) Success
 **/
int init_player(Player *player)
{
	if (player == NULL)
		return (1);
	player->width = 10;
	player->height = 10;
	player->x = 100;
	player->y = 240;
	player->ang = 60.0;
	player->dx = 0.0;
	player->dy = 0.0;
	return (0);
}

/**
 * init_map - initializes map
 * @map: Input, map
 *
 * Return: (0) Success
 **/

int init_map(Grid *map)
{
	int i;

	if (map == NULL)
		return (1);

	map->draw = true;
	map->scale = 0;
	map->gridX = 12;
	map->gridY = 12;
	map->gridS = 64;

	map->DOF = map->gridX;

	for (i = 0; i < (map->gridX * map->gridY); i++)
		map->grid[i] = grid[i];

	return (0);
}

/**
 * init_instance - initializes window and renderer
 * @win: Input, struct with window and renderer
 * Return: (0) on successful window creation
 **/
int init_instance(SDL_Instance *win)
{
	if (win == NULL)
		return (1);

	win->width = 720;
	win->height = 480;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		return (1);
	}

	win->window = SDL_CreateWindow("Maze",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				720,
				480,
				0);

	if (!win->window)
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	win->renderer = SDL_CreateRenderer(win->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!win->renderer)
	{
		SDL_DestroyWindow(win->window);
		fprintf(stderr, "%s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}
