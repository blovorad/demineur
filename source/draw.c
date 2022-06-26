/*
Auteur Gautier Levesque
06/06/2022
*/

#include "draw.h"

void set_color(SDL_Renderer *renderer, SDL_Color color){

	if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0){

		SDL_Log("SDL_SetRenderDrawColor failed :%s\n", SDL_GetError());
		exit(1);
	}
}

void draw_rect(SDL_Renderer *renderer, const SDL_Rect rect, SDL_Color color){

	set_color(renderer, color);

	if(SDL_RenderDrawRect(renderer, &rect) < 0){

		SDL_Log("SDL_RenderDrawRect failed :%s\n", SDL_GetError());
		exit(1);
	}
}

void fill_rect(SDL_Renderer *renderer, const SDL_Rect rect, SDL_Color color){

	set_color(renderer, color);

	if(SDL_RenderFillRect(renderer, &rect) < 0){

		SDL_Log("SDL_RenderFillRect failed :%s\n", SDL_GetError());
		exit(1);
	}
}

void draw_sprite_ex(SDL_Renderer *renderer, Tab_texture *tab_texture, const Sprite sprite){

	assert(renderer != NULL);
	assert(tab_texture != NULL);

	if(SDL_RenderCopyEx(renderer, get_texture(tab_texture, sprite.index_texture), &sprite.source, &sprite.position, sprite.angle, &sprite.center, sprite.flip) < 0){

		SDL_Log("SDL_RenderCopyEx failed :%s\n", SDL_GetError());
		exit(1);
	}
}

void draw_sprite(SDL_Renderer *renderer, Tab_texture *tab_texture, const Sprite sprite){

	assert(renderer != NULL);
	assert(tab_texture != NULL);

	if(SDL_RenderCopy(renderer, get_texture(tab_texture, sprite.index_texture), &sprite.source, &sprite.position) < 0){

		SDL_Log("SDL_RenderCopy failed :%s\n", SDL_GetError());
		exit(1);
	}
}

Sprite creat_sprite(SDL_Renderer *renderer, Tab_texture *tab_texture, const char *texture_path, const SDL_Rect position, const SDL_Rect source, const Hit_box hit_box, const int taking_source){

	assert(renderer != NULL);
	assert(tab_texture != NULL);
	assert(texture_path != NULL);
	Sprite sprite;

	sprite.index_texture = get_index_texture(renderer, tab_texture, texture_path);

	sprite.position.x = position.x;
	sprite.position.y = position.y;
	sprite.position.w = position.w;
	sprite.position.h = position.h;

	if(taking_source == 0){

		sprite.source.x = 0;
		sprite.source.y = 0;
		if(SDL_QueryTexture(get_texture(tab_texture, sprite.index_texture), NULL, NULL, &sprite.source.w, &sprite.source.h) < 0){

			SDL_Log("SDL_QueryTexture failed: %s\n", SDL_GetError());
			exit(1);
		}
	}
	else{

		sprite.source.x = source.x;
		sprite.source.y = source.y;
		sprite.source.w = source.w;
		sprite.source.h = source.h;
	}

	sprite.hit_box.position.x = hit_box.position.x;
	sprite.hit_box.position.y = hit_box.position.y;
	sprite.hit_box.position.w = hit_box.position.w;
	sprite.hit_box.position.h = hit_box.position.h;
	sprite.hit_box.color.r = hit_box.color.r;
	sprite.hit_box.color.g = hit_box.color.g;
	sprite.hit_box.color.b = hit_box.color.b;
	sprite.hit_box.color.a = hit_box.color.a;

	sprite.angle = 0;

	sprite.center.x = sprite.position.w / 2;
	sprite.center.y = sprite.position.h / 2;

	sprite.flip = SDL_FLIP_NONE;

	return sprite;
}

void destroy_sprite(Tab_texture *tab_texture, Sprite *sprite){

	remove_current_use_texture(tab_texture, sprite->index_texture);

	sprite->index_texture = -1;
}