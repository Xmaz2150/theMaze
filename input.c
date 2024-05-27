#include "maze.h"

/**
 * key_events - listens to key presses
 * Return: (0) Success
 **/
int key_events(void)
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
					printf("Left key was pressed\n");
				if (key.keysym.sym == SDLK_RIGHT)
					printf("Right key was pressed\n");
				if (key.keysym.sym == SDLK_UP)
					printf("Up key was pressed\n");
				if (key.keysym.sym == SDLK_DOWN)
					printf("Down key was pressed\n");
				break;
		}
	}
	return (0);
}
