#ifndef MAZE_H_
#define MAZE_H_

#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct SDL_Instance {
	SDL_Window *window;
	SDL_Renderer *renderer;
	int width;
	int height;
	
} SDL_Instance;

typedef struct Player {
	int width;
	int height;
	int x;
	int y;
	float ang;
} Player;

int init_instance(SDL_Instance *win);
int init_player(Player *player);

void draw_stuff(SDL_Instance *win, Player *player);
void draw_rect(SDL_Instance *win, int beginX, int beginY, int width, int height);

int key_events(void);

#endif /* MAZE_H_ */
