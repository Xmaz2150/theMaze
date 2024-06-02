#ifndef MAZE_H_
#define MAZE_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#define PI 3.14159

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
	float dx;
	float dy;
} Player;

typedef struct Grid {
	int gridX;
	int gridY;
	int gridS;
	int grid[64];
} Grid;

typedef struct Vector {
	float x;
	float y;
	float dist;
} Vector;

typedef struct Math {
	double sin_lookup[360];
	double cos_lookup[360];
} Math;

void precompute_lookup_tables(Math *math);
float deg_to_rad(float a);
int fix_ang(int a);

int m_init(Player *player, Grid *map, Math *math);
int init_instance(SDL_Instance *win);
int init_player(Player *player);
int init_map(Grid *map);

void draw_stuff(SDL_Instance *win, Player *player, Grid *map, Math *math);
void draw_rect(SDL_Instance *win, int beginX, int beginY, int width, int height);
void draw_line(SDL_Instance *win, int bginX, int bginY, int endX, int endY);

void draw_ray(SDL_Instance *win, Player *player, Grid *map, Math *math);
Vector *x_rays(Player *player, Grid *map, float ra, float Tan, Math *math);
Vector *y_rays(Player *player, Grid *map, float ra, float Tan, Math *math);

int key_events(Player *player, Math *math, Grid *map);

#endif /* MAZE_H_ */
