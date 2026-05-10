#ifndef TYPES_H_
#define TYPES_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

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

	int scale;
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
#endif /* TYPES_H_ */