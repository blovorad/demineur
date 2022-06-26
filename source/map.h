/*
Auteur Gautier Levesque
09/06/2022
*/

#ifndef __MAP_H__
#define __MAP_H__

#include "core.h"

#include "draw.h"

#define TILE_WIDTH_ASSET 16
#define TILE_HEIGHT_ASSET 16

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

/*id des tiles*/
typedef enum type_tile{

	UN,
	DEUX,
	TROIS,
	QUATRE,
	CINQ,
	SIX,
	SEPT,
	HUIT,
	BLOCK,
	FLAG,
	BOMB,
	NONE

}Type_tile;

/*case d'une map*/
typedef struct tile{

	Sprite sprite;
	Type_tile type;
	int nb_bomb;
	SDL_bool reveal;
	SDL_bool is_flag;
	SDL_bool is_hoover;
	SDL_bool is_pressed;
}Tile;

/*la map entiere*/
typedef struct map{

	Tile **map;
	Tile **bomb;
	int map_size_x;
	int map_size_y;
	int map_width;
	int map_height;
	int offset_x;
	int offset_y;
	int nb_bomb;
	int nb_reveal;
	int nb_to_reveal;
}Map;

/*initialisation de la map*/
Map init_map(SDL_Renderer *renderer, Tab_texture *tab_texture, int map_size_x, int map_size_y, int nb_bomb);

/*affichage du nombre de bomb autour*/
Type_tile change_type_bomb(int number);

/*recherche de la place de l'index*/
SDL_Rect get_source_of_tile(int index);

/*dessin de la map*/
void draw_map(SDL_Renderer *renderer, Tab_texture *tab_texture, Map map);

/*effacement de la carte*/
void clean_map(Tab_texture *tab_texture, Map *map);

#endif