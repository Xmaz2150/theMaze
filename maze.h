#ifndef MAZE_H_
#define MAZE_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define PI 3.14159
#define MAZE \
	Player *player = this->player; \
	Grid *map = this->map; \
	Math *math = this->math;

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
	bool draw;

	int DOF;
	int gridX;
	int gridY;
	int gridS;
	int grid[400];
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

typedef struct Maze {
	Player *player;
	Grid *map;
	Math *math;
} Maze;

void precompute_lookup_tables(Math *math);
float deg_to_rad(float a);
int fix_ang(int a);

int m_init(Maze *maze);
int init_instance(SDL_Instance *win);
int init_player(Player *player);
int init_map(Grid *map);

void draw_stuff(SDL_Instance *win, Maze *maze);
void draw_rect(SDL_Instance *win, int beginX, int beginY, int width, int height);
void draw_line(SDL_Instance *win, int bginX, int bginY, int endX, int endY);
void draw_grid(SDL_Instance *win, Grid *map);

void draw_ray(SDL_Instance *win, Maze *maze);
Vector *horizontal_lines(Maze *maze, float ra, float Tan);
Vector *vertical_lines(Maze *maze, float ra, float Tan);

int key_events(Maze *maze);
void update_pos(Maze *maze, float dx, float dy, char flag);

#endif /* MAZE_H_ */
