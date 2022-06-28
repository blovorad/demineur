/*
Auteur Gautier Levesque
27/06/2022
*/

#include "font.h"

Tab_text init_tab_text(const int max_text){

	Tab_text tab_text;

	tab_text.nb_text = max_text;
	tab_text.text = malloc(sizeof(Text) * max_text);
	if(tab_text.text == NULL){

		perror("malloc failed");
		exit(1);
	}

	SDL_Rect rect = {0,0,0,0};
	SDL_Color color = {0,0,0,0};
	Hit_box hit_box = {rect, color};

	for(int i = 0; i < max_text; i++){

		tab_text.text[i].sprite.hit_box = hit_box;
		tab_text.text[i].sprite.angle = 0;
		tab_text.text[i].sprite.flip = SDL_FLIP_NONE;
		tab_text.text[i].texture = NULL;
		tab_text.text[i].current_use = 0;
		tab_text.text[i].text = NULL;
	}

	return tab_text;
}

TTF_Font *open_font(const char *path, const int font_size){

	assert(path != NULL);

	TTF_Font *font = TTF_OpenFont(path, font_size);

	if(font == NULL){

		SDL_Log("TTF_openFont failed : %s\n", TTF_GetError());
		exit(1);
	}

	return font;
}

void creat_text(SDL_Renderer *renderer, const char *text, SDL_Rect position, SDL_Color text_color, TTF_Font *font, Tab_text *tab_text){

	assert(text != NULL);

	/*recherche d'une place*/
	int index = 0;
	while(index < tab_text->nb_text && tab_text->text[index].current_use > 0){

		index += 1;
	}
	if(index == tab_text->nb_text){

		index -= 1;
	}

	/*place trouver creation*/
	tab_text->text[index].sprite.position = position;
	tab_text->text[index].current_use += 1;
	tab_text->text[index].sprite.index_texture = index;
	int size = strlen(text) + 1;
	tab_text->text[index].text = malloc(sizeof(char) * size);
	if(tab_text->text[index].text == NULL){

		perror("malloc failed");
		exit(1);
	}
	strcpy(tab_text->text[index].text, text);
	tab_text->text[index].text[size] = '\0';

	SDL_Surface *surface = TTF_RenderText_Solid(font, text, text_color);
	if(surface == NULL){

		SDL_Log("TTF_RenderText_Solid failed : %s\n", TTF_GetError());
		exit(1);
	}

	tab_text->text[index].texture = SDL_CreateTextureFromSurface(renderer, surface);
	free(surface);
	surface = NULL;

	if(tab_text->text[index].texture == NULL){

		SDL_Log("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	if(SDL_QueryTexture(tab_text->text[index].texture, NULL, NULL, &tab_text->text[index].sprite.source.w, &tab_text->text[index].sprite.source.h) < 0){

		SDL_Log("SDL_QueryTexture failed: %s\n", SDL_GetError());
		exit(1);
	}
	tab_text->text[index].sprite.center.x = tab_text->text[index].sprite.position.w / 2;
	tab_text->text[index].sprite.center.y = tab_text->text[index].sprite.position.h / 2;
}

void draw_text(SDL_Renderer *renderer, Tab_text *tab_text){

	for(int i = 0; i < tab_text->nb_text; i++){

		if(tab_text->text[i].current_use > 0){

			draw_sprite_ex(renderer, NULL, tab_text->text[i].texture, tab_text->text[i].sprite);
		}
	}
}

void close_font(TTF_Font **font){

	assert(*font != NULL);

	if(*font != NULL){

		TTF_CloseFont(*font);
		*font = NULL;
	}
}

void remove_one_current_use_text(Tab_text *tab_text, const char *text){

	assert(tab_text != NULL && text != NULL);

	int index = 0;
	SDL_bool found = SDL_FALSE;

	while(found == SDL_FALSE && index < tab_text->nb_text){

		if(tab_text->text[index].current_use > 0){
			
			if(strcmp(text, tab_text->text[index].text) == 0){

				tab_text->text[index].current_use -= 1;
				if(tab_text->text[index].current_use == 0){

					printf("on clean un text : %s\n", text);
					clean_text(tab_text, index);
				}
			}
		}
		index += 1;
	}
}

void clean_text(Tab_text *tab_text, const int index){

	if(tab_text->text[index].texture != NULL){

		SDL_DestroyTexture(tab_text->text[index].texture);
		tab_text->text[index].texture = NULL;
	}
	if(tab_text->text[index].text != NULL){

		free(tab_text->text[index].text);
		tab_text->text[index].text = NULL;
	}
}	

void clean_tab_text(Tab_text *tab_text){

	if(tab_text->text != NULL){

		for(int i = 0; i < tab_text->nb_text; i++){

			clean_text(tab_text, i);
		}

		free(tab_text->text);
		tab_text->text = NULL;
	}
}