/*
Auteur Gautier Levesque
06/06/2022
*/

#include "init.h"

void init(Window *window, Input *input, Mouse *mouse, Tab_texture *tab_texture, Map *map, Tab_text *tab_text){

	if(SDL_Init(SDL_INIT_VIDEO) < 0){

		SDL_Log("SDL_init failed : %s\n", SDL_GetError());
		exit(1);
	}

	if(TTF_Init() == -1){

		SDL_Log("TTF_init failed : %s\n", TTF_GetError());
		exit(1);
	}

	*window = creat_window("./source/files/configuration.txt");
	*input = init_input();
	*mouse = init_mouse();

	*tab_text = init_tab_text(10);
	*tab_texture = creat_tab_texture("./source/graphics");

	*map = init_map(window->renderer, tab_texture, 20, 15, 20);
}