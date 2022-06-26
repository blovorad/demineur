/*
Auteur Gautier Levesque
06/06/2022
*/

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "configuration.h"

#include <SDL.h>

/*definition de la structure d'une fenetre*/
typedef struct window{

	Configuration configuration;
	SDL_Window *window;
	SDL_Renderer *renderer;
}Window;

/*creation de la fenetre et du renderer*/
Window creat_window(const char *path);

/*liberation memoire de la window*/
void free_window(Window *window);

#endif