/*
Auteur Gautier Levesque
09/06/2022
*/

#include "map.h"

Map init_map(SDL_Renderer *renderer, Tab_texture *tab_texture, int map_size_x, int map_size_y, int nb_bomb){

	assert(map_size_x > 0);
	assert(map_size_y > 0);
	assert(nb_bomb > 0);
	assert(tab_texture != NULL);
	assert(renderer != NULL);

	Map map;

	map.nb_reveal = 0;
	map.nb_to_reveal = map_size_x * map_size_y - nb_bomb;
	map.map_size_x = map_size_x;
	map.map_size_y = map_size_y;
	map.offset_x = 75;
	map.offset_y = 50;
	map.map_width = map_size_x * TILE_WIDTH;
	map.map_height = map_size_y * TILE_HEIGHT;
	map.nb_bomb = nb_bomb;

	map.map = malloc(sizeof(Tile) * map.map_size_y);
	if(map.map == NULL){

		perror("malloc failed");
		exit(1);
	}
	for(int i = 0; i < map.map_size_y; i++){

		map.map[i] = malloc(sizeof(Tile) * map.map_size_x);
		if(map.map[i] == NULL){

			perror("malloc failed");
			exit(1);
		}
	}

	for(int i = 0; i < map.map_size_y; i++){

		for(int j = 0; j < map_size_x; j++){

			Type_tile type_tile = NONE;
			SDL_Rect pos = {map.offset_x + (j*TILE_WIDTH), map.offset_y + (i*TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT};
			Hit_box hit_box = {{map.offset_x + (j*TILE_WIDTH), map.offset_y + (i*TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT}, {255,255,255,255}};
			SDL_Rect source = get_source_of_tile(type_tile);

			map.map[i][j].sprite = creat_sprite(renderer, tab_texture, "./source/graphics/spritesheet/sheet_demineur.png", pos, source, hit_box, 1);
			map.map[i][j].type = type_tile;
			map.map[i][j].nb_bomb = 0;
			map.map[i][j].reveal = SDL_FALSE;
			map.map[i][j].is_flag = SDL_FALSE;
			map.map[i][j].is_hoover = SDL_FALSE;
		}
	}

	map.bomb = malloc(sizeof(Tile) * map.nb_bomb);
	if(map.bomb == NULL){

		perror("malloc failed");
		exit(1);
	}

	int bomb_placed = 0;

	while(bomb_placed < nb_bomb){

		int i = rand() % map.map_size_y;
		int j = rand() % map.map_size_x;

		if(map.map[i][j].type != BOMB){

			map.map[i][j].type = BOMB;
			map.bomb[bomb_placed] = &map.map[i][j];
			map.map[i][j].sprite.source = get_source_of_tile(map.map[i][j].type);
			bomb_placed += 1;

			if((j-1) >= 0 && map.map[i][j-1].type != BOMB){
				map.map[i][j-1].nb_bomb += 1;
				map.map[i][j-1].type = change_type_bomb(map.map[i][j-1].nb_bomb);
				map.map[i][j-1].sprite.source = get_source_of_tile(map.map[i][j-1].type);
			}
			if((j+1) < map.map_size_x && map.map[i][j+1].type != BOMB){
				map.map[i][j+1].nb_bomb += 1;
				map.map[i][j+1].type = change_type_bomb(map.map[i][j+1].nb_bomb);
				map.map[i][j+1].sprite.source = get_source_of_tile(map.map[i][j+1].type);
			}
			if((j-1) >= 0 && (i-1) >= 0 && map.map[i-1][j-1].type != BOMB){
				map.map[i-1][j-1].nb_bomb += 1;
				map.map[i-1][j-1].type = change_type_bomb(map.map[i-1][j-1].nb_bomb);
				map.map[i-1][j-1].sprite.source = get_source_of_tile(map.map[i-1][j-1].type);
			}
			if((i-1) >= 0 && map.map[i-1][j].type != BOMB){
				map.map[i-1][j].nb_bomb += 1;
				map.map[i-1][j].type = change_type_bomb(map.map[i-1][j].nb_bomb);
				map.map[i-1][j].sprite.source = get_source_of_tile(map.map[i-1][j].type);
			}
			if((j+1) < map.map_size_x && (i-1) >= 0 && map.map[i-1][j+1].type != BOMB){
				map.map[i-1][j+1].nb_bomb += 1;
				map.map[i-1][j+1].type = change_type_bomb(map.map[i-1][j+1].nb_bomb);
				map.map[i-1][j+1].sprite.source = get_source_of_tile(map.map[i-1][j+1].type);
			}
			if((j-1) >= 0 && (i+1) < map.map_size_y && map.map[i+1][j-1].type != BOMB){
				map.map[i+1][j-1].nb_bomb += 1;
				map.map[i+1][j-1].type = change_type_bomb(map.map[i+1][j-1].nb_bomb);
				map.map[i+1][j-1].sprite.source = get_source_of_tile(map.map[i+1][j-1].type);
			}
			if((i+1) < map.map_size_y && map.map[i+1][j].type != BOMB){
				map.map[i+1][j].nb_bomb += 1;
				map.map[i+1][j].type = change_type_bomb(map.map[i+1][j].nb_bomb);
				map.map[i+1][j].sprite.source = get_source_of_tile(map.map[i+1][j].type);
			}
			if((j+1) < map.map_size_x && (i+1) < map.map_size_y && map.map[i+1][j+1].type != BOMB){
				map.map[i+1][j+1].nb_bomb += 1;
				map.map[i+1][j+1].type = change_type_bomb(map.map[i+1][j+1].nb_bomb);
				map.map[i+1][j+1].sprite.source = get_source_of_tile(map.map[i+1][j+1].type);
			}
		}
	}

	return map;
}

Type_tile change_type_bomb(int number){

	Type_tile type = number;

	switch(number){

		case 1:
			type = UN;
			break;
		case 2:
			type = DEUX;
			break;
		case 3:
			type = TROIS;
			break;
		case 4:
			type = QUATRE;
			break;
		case 5:
			type = CINQ;
			break;
		case 6:
			type = SIX;
			break;
		case 7:
			type = SEPT;
			break;
		case 8:
			type = HUIT;
			break;

		default:
			type = TROIS;
			break;
	}

	return type;
}

SDL_Rect get_source_of_tile(int index){

	SDL_Rect source;

	switch(index){

		case UN:
			source.x = 0;
			source.y = 0;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case DEUX:
			source.x = 16;
			source.y = 0;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case TROIS:
			source.x = 32;
			source.y = 0;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case QUATRE:
			source.x = 48;
			source.y = 0;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case CINQ:
			source.x = 64;
			source.y = 0;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case SIX:
			source.x = 80;
			source.y = 0;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case SEPT:
			source.x = 64;
			source.y = 16;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case HUIT:
			source.x = 80;
			source.y = 16;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case BLOCK:
			source.x = 0;
			source.y = 16;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case FLAG:
			source.x = 16;
			source.y = 16;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case BOMB:
			source.x = 32;
			source.y = 16;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;
		case NONE:
			source.x = 48;
			source.y = 16;
			source.w = TILE_WIDTH_ASSET;
			source.h = TILE_HEIGHT_ASSET;
			break;

		default:
			break;
	}

	return source;
}

void draw_map(SDL_Renderer *renderer, Tab_texture *tab_texture, Map map){

	for(int i = 0; i < map.map_size_y; i++){

		for(int j = 0; j < map.map_size_x; j++){

			if(map.map[i][j].reveal == SDL_TRUE){

				draw_sprite(renderer, tab_texture, map.map[i][j].sprite);
			}
			else{

				if(map.map[i][j].is_flag == SDL_TRUE){

					SDL_Rect source = get_source_of_tile(FLAG);
					Sprite spr = map.map[i][j].sprite;
					spr.source = source;
					draw_sprite(renderer, tab_texture, spr);
				}
				else{

					SDL_Rect source = get_source_of_tile(BLOCK);
					Sprite spr = map.map[i][j].sprite;
					spr.source = source;
					draw_sprite(renderer, tab_texture, spr);
					if(map.map[i][j].is_hoover == SDL_TRUE){

						if(map.map[i][j].is_pressed == SDL_TRUE){

							SDL_Rect source = get_source_of_tile(NONE);
							Sprite spr = map.map[i][j].sprite;
							spr.source = source;
							draw_sprite(renderer, tab_texture, spr);
							SDL_Color color = {120,200,150,100};
							fill_rect(renderer, spr.position, color);
						}
						else{

							SDL_Color color = {120,200,150,100};
							fill_rect(renderer, spr.position, color);
						}
					}
				}
			}
		}
	}
}

void clean_map(Tab_texture *tab_texture, Map *map){

	if(map->bomb != NULL){

		free(map->bomb);
		map->bomb = NULL;
	}

	if(map->map != NULL){

		for(int i = 0; i < map->map_size_y; i++){

			if(map->map[i] != NULL){

				for(int j = 0; j < map->map_size_x; j++){

					remove_current_use_texture(tab_texture, map->map[i][j].sprite.index_texture);
					map->map[i][j].nb_bomb = 0;
				}
				free(map->map[i]);
				map->map[i] = NULL;
			}
		}
		free(map->map);
		map->map = NULL;
	}
}