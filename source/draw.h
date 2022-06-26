/*
Auteur Gautier Levesque
06/06/2022
*/

#ifndef __DRAW_H__
#define __DRAW_H__

#include <SDL.h>

#include "texture.h"

/*definition d'une hitbox*/
typedef struct hit_box{

	SDL_Rect position;
	SDL_Color color;
}Hit_box;

/*definition d'un sprite*/
typedef struct sprite{

	int index_texture;
	SDL_Rect position;
	SDL_Rect source;
	Hit_box hit_box;
	double angle;
	SDL_Point center;
	SDL_RendererFlip flip;
}Sprite;

/*creation d'un sprite*/
Sprite creat_sprite(SDL_Renderer *renderer, Tab_texture *tab_texture, const char *texture_path, const SDL_Rect position, const SDL_Rect source, const Hit_box hit_box, const int taking_source);

/*dessin d'un sprite*/
void draw_sprite(SDL_Renderer *renderer, Tab_texture *tab_texture, const Sprite sprite);

/*dessin d'un sprite rotatif*/
void draw_sprite_ex(SDL_Renderer *renderer, Tab_texture *tab_texture, const Sprite sprite);

/*application d'une couleur*/
void set_color(SDL_Renderer *renderer, SDL_Color color);

/*dessin d'un rectangle*/
void draw_rect(SDL_Renderer *renderer, const SDL_Rect rect, SDL_Color color);

/*dessin d'un rectangle remplis*/
void fill_rect(SDL_Renderer *renderer, const SDL_Rect rect, SDL_Color color);

/*destruction d'un sprite*/
void destroy_sprite(Tab_texture *tab_texture, Sprite *sprite);

#endif