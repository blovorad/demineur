/*
Auteur Gautier Levesque
09/06/2022
*/

#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <SDL.h>

#include <stdio.h>

#include "core.h"

#include "map.h"

/*defintion de la structure d'une souris*/
typedef struct mouse{

	SDL_Point position;
	SDL_bool left_click;
	SDL_bool right_click;
	SDL_bool old_left_click;
	SDL_bool old_right_click;
	Tile *tile;
	int index_tile_x;
	int index_tile_y;
}Mouse;

/*initialisation de la souris*/
Mouse init_mouse(void);

/*recuperation de la position de la souris*/
void get_mouse_pos(Mouse *mouse);

#endif