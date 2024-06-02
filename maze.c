#include "maze.h"
/*gcc -o maze maze.c -Iinclude/SDL2 -Llib -lmingw32 -lSDL2main -lSDL2*/
/*gcc -Wall -Werror -Wextra -pedantic *.c -o maze -lSDL2 -lm*/

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
	Player player;
	Grid map;
	Math math;

	if (init_instance(&win) == 1 || m_init(&player, &map, &math))
		return (1);

	while (1)
	{
		SDL_SetRenderDrawColor(win.renderer, 200, 200, 200, 255);
		SDL_RenderClear(win.renderer);

		player.dx = math.cos_lookup[(int)player.ang % 360];
		player.dy = -math.sin_lookup[(int)player.ang % 360];
		if (key_events(&player, &math, &map) == 1)
			break;

		draw_stuff(&win, &player, &map, &math);
		SDL_RenderPresent(win.renderer);
		SDL_Delay(10);
	}

	SDL_DestroyRenderer(win.renderer);
	SDL_DestroyWindow(win.window);
	SDL_Quit();

	return (0);
}
