/*
Auteur Gautier Levesque
09/06/2022
*/

#ifndef __INIT_H__
#define __INIT_H__

#include <SDL.h>

#include "core.h"

#include "window.h"
#include "input.h"

/*initialisation du programme*/
void init(Window *window, Input *input, Mouse *mouse, Tab_texture *tab_texture, Map *map);

#endif