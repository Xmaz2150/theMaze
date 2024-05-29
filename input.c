#include "maze.h"

/**
 * key_events - listens to key presses
 * @player: Input, player
 *
 * Return: (0) Success
 **/
int key_events(Player *player, Math *math)
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
				{
					player->x += player->dx * 5;
					player->y += player->dy * 5;
				}
				if (key.keysym.sym == SDLK_DOWN)
				{
					player->x -= player->dx * 5;
					player->y -= player->dy * 5;
				}
				break;
		}
	}
	return (0);
}
