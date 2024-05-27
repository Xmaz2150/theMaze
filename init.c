#include "maze.h"

/**
 * m_init - initializes integral types
 * @win: Input, main game window
 * @player: Input, player
 *
 * Return: (0) Success
 **/
int m_init(SDL_Instance *win, Player *player)
{
	(void)player;
	(void)win;
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
	player->x = 64;
	player->y = 240;
	player->ang = 60.0;
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
