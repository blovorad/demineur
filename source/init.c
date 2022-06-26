/*
Auteur Gautier Levesque
06/06/2022
*/

#include "init.h"

void init(Window *window, Input *input, Mouse *mouse, Tab_texture *tab_texture, Map *map){

	if(SDL_Init(SDL_INIT_VIDEO) < 0){

		SDL_Log("SDL_init failed : %s\n", SDL_GetError());
		exit(1);
	}

	*window = creat_window("./source/files/configuration.txt");
	*input = init_input();
	*mouse = init_mouse();

	*tab_texture = creat_tab_texture("./source/graphics");

	*map = init_map(window->renderer, tab_texture, 20, 15, 20);
}