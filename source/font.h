/*
Auteur Gautier Levesque
27/06/2022
*/

#ifndef __FONT_H__
#define __FONT_H__

#include "core.h"

#include "draw.h"

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct text{

	Sprite sprite;
	SDL_Texture *texture;
	char *text;
	int current_use;
}Text;

typedef struct tab_text{

	int nb_text;
	Text *text;
}Tab_text;

/*initialisation des tableaux de textes*/
Tab_text init_tab_text(const int max_text);

/*ouverture d'une font*/
TTF_Font *open_font(const char *path, const int font_size);

/*creation d'un texte*/
void creat_text(SDL_Renderer *renderer, const char *text, SDL_Rect position, SDL_Color text_color, TTF_Font *font, Tab_text *tab_text);

/*on dit qu'une texture n'utilise plus ce texte*/
void remove_one_current_use_text(Tab_text *tab_text, const char *text);

/*dessin des textes*/
void draw_text(SDL_Renderer *renderer, Tab_text *tab_text);

/*destruction d'un texte*/
void clean_text(Tab_text *tab_text, const int index);

/*clean du tableau de texte*/
void clean_tab_text(Tab_text *tab_text);

/*fermeture d'une font*/
void close_font(TTF_Font **font);

#endif