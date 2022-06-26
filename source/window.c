/*
Auteur Gautier Levesque
06/06/2022
*/

#include "window.h"

Window creat_window(const char *path){
	
	assert(path != NULL);

	Configuration configuration = load_configuration_file(path);

	Window window;

	char *title = configuration.title;
	int pos_x = configuration.window_pos_x;
	int pos_y = configuration.window_pos_y;
	int width = configuration.window_width;
	int height = configuration.window_height;

	SDL_Window *screen = SDL_CreateWindow(title, pos_x, pos_y, width, height, configuration.flag_window);

	if(screen == NULL){

		SDL_Log("SDL_CreateWindow failed : %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, configuration.flag_renderer);
	if(renderer == NULL){

		SDL_Log("SDL_CreateRenderer failed : %s\n", SDL_GetError());
		exit(1);
	}

	window.window = screen;
	window.renderer = renderer;
	window.configuration = configuration;

	SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;

	if(SDL_SetRenderDrawBlendMode(window.renderer, blendMode)){

		SDL_Log("SDL_SetRenderDrawBlendMode failed : %s\n", SDL_GetError());
		exit(1);
	}

	return window;
}

void free_window(Window *window){

	free(window->configuration.path);
	window->configuration.path = NULL;

	SDL_DestroyRenderer(window->renderer);
	window->renderer = NULL;
	
	SDL_DestroyWindow(window->window);
	window->window = NULL;
}