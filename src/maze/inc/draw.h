#ifndef DRAW_H_
#define DRAW_H_

#include <SDL2/SDL_image.h>

void draw_stuff(SDL_Instance *win, Maze *maze);
void draw_rect(SDL_Instance *win, int beginX, int beginY, int width, int height);
void draw_l(SDL_Instance *win, int bginX, int bginY, int endX, int endY);
void draw_grid(SDL_Instance *win, Grid *map);

void display_image(SDL_Instance *win, const char *image_path);
#endif /* DRAW_H_ */