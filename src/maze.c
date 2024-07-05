#include "../inc/maze.h"

/*gcc -o maze maze.c -Iinclude/SDL2 -Llib -lmingw32 -lSDL2main -lSDL2*/
/*gcc -Wall -Werror -Wextra -pedantic src/all.c -o maze -lSDL2 -lSDL2_image -lm*/

/**
 * main - entry point for the Maze
 *@argc: Input, argument count
 * @argv: Input, arguments
 * Return: (0) success
 **/
int main(int argc, char *argv[])
{

	(void)argc;
	(void)argv;

	SDL_Instance win;

	Maze maze;

	Player player;
	Grid map;
	Math math;

	maze.player = &player;
	maze.map = &map;
	maze.math = &math;

	if (init_instance(&win) == 1 || m_init(&maze))
		return (1);

	while (1)
	{
		SDL_SetRenderDrawColor(win.renderer, 200, 200, 200, 255);
		SDL_RenderClear(win.renderer);

		maze.player->dx = maze.math->cos_lookup[(int)maze.player->ang % 360];
		maze.player->dy = -maze.math->sin_lookup[(int)maze.player->ang % 360];
		if (key_events(&maze) == 1)
			break;

		draw_stuff(&win, &maze);
		SDL_RenderPresent(win.renderer);
		SDL_Delay(10);
	}

	SDL_DestroyRenderer(win.renderer);
	SDL_DestroyWindow(win.window);
	SDL_Quit();

	return (0);
}
