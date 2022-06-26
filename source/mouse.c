/*
Auteur Gautier Levesque
09/06/2022
*/

#include "mouse.h"

Mouse init_mouse(void){

	SDL_Point p;
	SDL_GetMouseState(&p.x, &p.y);

	Mouse mouse = {p, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, NULL, 0, 0};

	return mouse;
}

void get_mouse_pos(Mouse *mouse){

	SDL_GetMouseState(&mouse->position.x, &mouse->position.y);
}