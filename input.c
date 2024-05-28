#include "maze.h"

/**
 * key_events - listens to key presses
 * @player: Input, player
 *
 * Return: (0) Success
 **/
int key_events(Player *player)
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
					player->ang = fix_ang(player->ang + 1);
				if (key.keysym.sym == SDLK_RIGHT)
					player->ang = fix_ang(player->ang - 1);
				if (key.keysym.sym == SDLK_UP)
					player->y -= 5;
				if (key.keysym.sym == SDLK_DOWN)
					player->y += 5;
				break;
		}
	}
	return (0);
}
