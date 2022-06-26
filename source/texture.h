/*
Auteur Gautier Levesque
07/06/2022
*/

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL.h>
#include <SDL_image.h>

#include "directory.h"

/*definition d'un texture*/
typedef struct texture{

	int current_use;
	char *path;
	SDL_Texture *texture;
}Texture;

/*definition du tableau de textures*/
typedef struct tab_texture{

	int nb_texture;
	Texture *textures;
}Tab_texture;

/*creation du tableau de texture*/
Tab_texture creat_tab_texture(const char *path);

/*comptage du nombre de texture*/
int count_nb_texture(File_file_tq file);

/*chargement d'une texture*/
SDL_Texture *creat_texture(SDL_Renderer *renderer, const char *path);

/*recuperation d'une texture pour le dessin*/
SDL_Texture *get_texture(Tab_texture *tab_texture, const int index);

/*recuperation de l'index d'une texture*/
int get_index_texture(SDL_Renderer *renderer, Tab_texture *tab_texture, const char *path);

/*enlever current_use sur une texture*/
void remove_current_use_texture(Tab_texture *tab_texture, const int index);

/*destruction d'un texture*/
void destroy_texture(Tab_texture *tab_texture, const int index);

#endif