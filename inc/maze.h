#ifndef MAZE_H_
#define MAZE_H_

#include "types.h"
#include "draw.h"
#include "math.h"

#define PI 3.14159
#define P_W 300
#define PLANE_H 200
#define DIST_TO_PLANE 277
#define SLICE_W 5
#define ANGLE_INC 1

#define MAZE \
	Player *player = this->player; \
	Grid *map = this->map; \
	Math *math = this->math; \
	int s = map->scale; \
	\
	(void)player; \
	(void)map; \
	(void)math; \
	(void)s;

int m_init(Maze *maze);
int init_instance(SDL_Instance *win);
int init_player(Player *player);
int init_map(Grid *map);

void draw_ray(SDL_Instance *win, Maze *maze);
Vector horizontal_lines(Maze *maze, float ra, float Tan);
Vector vertical_lines(Maze *maze, float ra, float Tan);
Vector cast_ray(Maze *maze, Vector *arr,  int dof, float dis);

int key_events(Maze *maze);
void update_pos(Maze *maze, float dx, float dy, char flag);

#endif /* MAZE_H_ */
