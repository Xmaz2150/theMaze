#include "../inc/maze.h"

/**
 * draw_stuff - draws graphics to window
 * @win: Input, window
 * @this: Input- player, grid & math
 **/
void draw_stuff(SDL_Instance *win, Maze *this)
{
	MAZE

	SDL_SetRenderDrawColor(win->renderer, 0, 0, 125, 255);
	draw_rect(win, 0, 0, 305, 100);
	SDL_SetRenderDrawColor(win->renderer, 0, 125, 0, 255);
	draw_rect(win, 0, 100, 305, 100);

	if (map->draw)
	{
		draw_grid(win, map);
		SDL_SetRenderDrawColor(win->renderer, 255, 0, 0, 255);
		draw_rect(win, (player->x / 10) + 320 - 2.5, (player->y / 10) - 2.5, 5, 5);
	}
	draw_ray(win, this);
	/**const char *weapons[] = {"assets/sprites/9mm.png", "assets/sprites/pump.png"};

	display_image(win, weapons[s]);**/
}

/**
 * draw_rect - draws rectplayer->ang to screen provided color is already set
 * @win: Input, window
 * @beginX: Input, starting point along x axis
 * @beginY: Input, starting point along y axis
 * @w: Input, rectplayer->ang width
 * @h: Input, rectplayer->ang height
 **/
void draw_rect(SDL_Instance *win, int beginX, int beginY, int w, int h)
{
	SDL_Rect fillRect = {beginX, beginY, w, h};

	SDL_RenderFillRect(win->renderer, &fillRect);
}

/**
 * draw_l - draws line to screen provided color is already set
 * @win: Input, window
 * @beginX: Input, starting point along x axis
 * @beginY: Input, starting point along y axis
 * @endX: Input, last point along x axis
 * @endY: Input, last point along y axis
 **/
void draw_l(SDL_Instance *win, int beginX, int beginY, int endX, int endY)
{
	SDL_RenderDrawLine(win->renderer,
		     beginX,
		     beginY,
		     endX,
		     endY
	);
}

/**
 * draw_grid - draws grid
 * @win: Input, window
 * @map: Input, map
 **/
void draw_grid(SDL_Instance *win, Grid *map)
{
	int x, y, xo, yo, idx, gridS;

	gridS = 7;
	for (y = 0; y < map->gridY; y++)
	{
		for (x = 0; x < map->gridX; x++)
		{
			idx = y * map->gridX + x;

			xo = x * gridS;
			yo = y * gridS;
			SDL_Rect fillRect = {xo + (320 - 2.5), yo - 2.5, gridS - 1, gridS - 1};

			if (map->grid[idx] == 1)
				SDL_SetRenderDrawColor(win->renderer, 255, 255, 0, 255);
			else
				SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(win->renderer, &fillRect);
		}
	}
}

/**
 * display_image - displays image to screen
 * @win: Input, window
 * @image_path: Input, path to image
 **/
void display_image(SDL_Instance *win, const char *image_path)
{
	SDL_Surface *image_surface;
	SDL_Texture *texture;

	image_surface = IMG_Load(image_path);
	if (image_surface == NULL)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
	}

	texture = SDL_CreateTextureFromSurface(win->renderer, image_surface);
	if (texture == NULL)
	{
		printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
	}

	SDL_Rect dest_rect = {P_W / 2, PLANE_H - 55, 0, 0};

	SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h);
	SDL_RenderCopy(win->renderer, texture, NULL, &dest_rect);

	SDL_FreeSurface(image_surface);
	SDL_DestroyTexture(texture);
}
