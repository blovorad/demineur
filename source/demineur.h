#ifndef __DEMINEUR_H__
#define __DEMINEUR_H__

/*include standards entrer/sortie et malloc*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "init.h"

/*verification hoover*/
void get_tile_hoover(Map *map, Mouse *mouse);

/*fonction qui dessine le jeu/fenetre*/
void draw(SDL_Renderer *renderer, Tab_texture *tab_texture, Map map);

/*verification de la victoire*/
SDL_bool check_victory(Map map);

/*verification de la case presser*/
void check_who_pressed(Map *map, Mouse *mouse);

/*fonction qui revele la map au depart d'une case*/
void reveal_map(int x, int y, Map *map);

/*fonction principale*/
int demineur(void);

#endif