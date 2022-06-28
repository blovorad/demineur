/*
Auteur Gautier Levesque
06/06/2022
*/

#include "demineur.h"

/*fonction principale*/
int demineur(void){

	srand(time(NULL));

	Window window;
	Input input;
	Mouse mouse;
	Tab_text tab_text;
	Tab_texture tab_texture;
	Map map;
	
	/*initialisation du jeu*/
	init(&window, &input, &mouse, &tab_texture, &map, &tab_text);

	Uint32 last_tick = SDL_GetTicks();
	Uint32 current_tick;
	double fps = (double)1000/(double)30;
	SDL_bool end_of_game = SDL_FALSE;

	SDL_Color text_color = {255,255,255,255};
	SDL_Rect text_pos = {200, 575, 400, 25};
	TTF_Font *font = open_font("./source/files/fonts/demineur_font.ttf", 50);

	creat_text(window.renderer, "Demineur produit par Blovorad", text_pos, text_color, font, &tab_text);
	close_font(&font);

	/*boucle du jeu*/
	while(update_input(&input, &mouse) == SDL_TRUE){

		current_tick = SDL_GetTicks();

		if(end_of_game == SDL_FALSE){

			get_mouse_pos(&mouse);

			get_tile_hoover(&map, &mouse);
			SDL_bool victory = SDL_FALSE;
			if(mouse.tile != NULL){

				if(mouse.tile->is_pressed == SDL_FALSE && ((mouse.left_click == SDL_TRUE && mouse.old_left_click == SDL_FALSE) || (mouse.right_click == SDL_TRUE && mouse.old_right_click == SDL_FALSE))){

					mouse.tile->is_pressed = SDL_TRUE;
					check_who_pressed(&map, &mouse);
				}
				else if(mouse.tile->is_pressed == SDL_TRUE){

					if(mouse.left_click == SDL_FALSE && mouse.old_left_click == SDL_TRUE){

						if(mouse.tile->is_flag == SDL_TRUE){

							mouse.tile->is_pressed = SDL_FALSE;
						}
						else{

							if(mouse.tile->type == BOMB){

								mouse.tile->reveal = SDL_TRUE;
								mouse.tile->is_pressed = SDL_FALSE;
								mouse.tile->is_hoover = SDL_FALSE;
								mouse.tile->is_flag = SDL_FALSE;
								mouse.tile = NULL;
								end_of_game = SDL_TRUE;
							}
							else{

								if(mouse.tile->reveal == SDL_FALSE){

									reveal_map(mouse.index_tile_x, mouse.index_tile_y, &map);
									mouse.tile->is_pressed = SDL_FALSE;
									mouse.tile->is_hoover = SDL_FALSE;
									mouse.tile->is_flag = SDL_FALSE;
									mouse.tile = NULL;
									victory = check_victory(map);
								}
							}
						}
					}
					else if(mouse.right_click == SDL_TRUE){

						if(mouse.tile->is_flag == SDL_FALSE){

							mouse.tile->is_pressed = SDL_FALSE;
							mouse.tile->is_hoover = SDL_FALSE;
							mouse.tile->is_flag = SDL_TRUE;
							mouse.tile = NULL;
							victory = check_victory(map);
						}
						else{

							mouse.tile->is_pressed = SDL_FALSE;
							mouse.tile->is_hoover = SDL_TRUE;
							mouse.tile->is_flag = SDL_FALSE;
							mouse.tile = NULL;
						}
					}
				}
			}

			if(victory == SDL_TRUE){

				end_of_game = SDL_TRUE;
				text_pos.x = 200;
				text_pos.y = 10;
				font = open_font("./source/files/fonts/demineur_font.ttf", 50);
				creat_text(window.renderer, "Victoire, pressez espace pour recommencer", text_pos, text_color, font, &tab_text);
				close_font(&font);
			}
			else if(end_of_game == SDL_TRUE){

				text_pos.x = 200;
				text_pos.y = 10;
				font = open_font("./source/files/fonts/demineur_font.ttf", 50);
				creat_text(window.renderer, "Defaite, pressez espace pour recommencer", text_pos, text_color, font, &tab_text);
				close_font(&font);
			}
		}
		else{

			if(input.space == SDL_TRUE){

				remove_one_current_use_text(&tab_text, "Victoire, pressez espace pour recommencer");
				remove_one_current_use_text(&tab_text, "Defaite, pressez espace pour recommencer");
				mouse.tile = NULL;
				clean_map(&tab_texture, &map);
				map = init_map(window.renderer, &tab_texture, 20, 15, 20);
				end_of_game = SDL_FALSE;
			}
		}

		mouse.old_left_click = mouse.left_click;
		mouse.old_right_click = mouse.right_click;

		/*dessin*/
		draw(window.renderer, &tab_texture, map, &tab_text);

		/*gestion des fps*/
		if(last_tick + fps > current_tick){

			SDL_Delay((last_tick + fps) - current_tick);
		}

		last_tick = current_tick;
	}

	/*quitter le programme*/
	clean_map(&tab_texture, &map);
	clean_tab_text(&tab_text);
	free_window(&window);
	TTF_Quit();
	SDL_Quit();

	printf("on arrete\n");
	return 0;
}

SDL_bool check_victory(Map map){

	int i = 0;
	SDL_bool no_bomb_flag = SDL_TRUE;

	while(no_bomb_flag == SDL_TRUE && i < map.nb_bomb){

		if(map.bomb[i]->is_flag == SDL_FALSE){

			no_bomb_flag = SDL_FALSE;
		}

		i += 1;
	}

	return no_bomb_flag && (map.nb_reveal == map.nb_to_reveal);
}

void reveal_map(int x, int y, Map *map){

	map->map[y][x].reveal = SDL_TRUE;
	map->nb_reveal += 1;

	if(map->map[y][x].type == NONE){

		if(x > 0 && map->map[y][x-1].type != BOMB && map->map[y][x-1].reveal == SDL_FALSE && map->map[y][x-1].is_flag == SDL_FALSE){

			reveal_map(x-1, y, map);
		}
		if(x > 0 && y > 0 && map->map[y-1][x-1].type != BOMB && map->map[y-1][x-1].reveal == SDL_FALSE && map->map[y-1][x-1].is_flag == SDL_FALSE){

			reveal_map(x-1, y-1, map);
		}
		if(x > 0 && y < (map->map_size_y-1) && map->map[y+1][x-1].type != BOMB && map->map[y+1][x-1].reveal == SDL_FALSE && map->map[y+1][x-1].is_flag == SDL_FALSE){

			reveal_map(x-1, y+1, map);
		}
		if(y > 0 && map->map[y-1][x].type != BOMB && map->map[y-1][x].reveal == SDL_FALSE && map->map[y-1][x].is_flag == SDL_FALSE){

			reveal_map(x, y-1, map);
		}
		if(y < (map->map_size_y - 1) && map->map[y+1][x].type != BOMB && map->map[y+1][x].reveal == SDL_FALSE && map->map[y+1][x].is_flag == SDL_FALSE){

			reveal_map(x, y+1, map);
		}
		if(x < (map->map_size_x - 1) && y > 0 && map->map[y-1][x+1].type != BOMB && map->map[y-1][x+1].reveal == SDL_FALSE && map->map[y-1][x+1].is_flag == SDL_FALSE){

			reveal_map(x+1, y-1, map);
		}
		if(x < (map->map_size_x - 1) && map->map[y][x+1].type != BOMB && map->map[y][x+1].reveal == SDL_FALSE && map->map[y][x+1].is_flag == SDL_FALSE){

			reveal_map(x+1, y, map);
		}
		if(x < (map->map_size_x - 1) && y < (map->map_size_y - 1) && map->map[y+1][x+1].type != BOMB && map->map[y+1][x+1].reveal == SDL_FALSE && map->map[y+1][x+1].is_flag == SDL_FALSE){

			reveal_map(x+1, y+1, map);
		}
	}
}

void get_tile_hoover(Map *map, Mouse *mouse){

	int j = floor(((double)mouse->position.x - (double)map->offset_x) / (double)TILE_WIDTH);
	int i = floor(((double)mouse->position.y - (double)map->offset_y) / (double)TILE_HEIGHT);

	if(i >= 0 && j >= 0 && i < map->map_size_y && j < map->map_size_x){

		if(map->map[i][j].reveal == SDL_FALSE){

			if(mouse->tile != &map->map[i][j]){

				if(mouse->tile != NULL && mouse->tile->is_pressed == SDL_FALSE){

					mouse->tile->is_hoover = SDL_FALSE;
					mouse->tile->is_pressed = SDL_FALSE;
					mouse->tile = &map->map[i][j];
					mouse->tile->is_hoover = SDL_TRUE;
				}
				else if(mouse->tile == NULL){

					mouse->tile = &map->map[i][j];
					mouse->tile->is_hoover = SDL_TRUE;
				}
			}
		}
		else{

			if(mouse->tile != NULL){

				mouse->tile->is_hoover = SDL_FALSE;
				mouse->tile->is_pressed = SDL_FALSE;
				mouse->tile = NULL;
			}
		}
	}
	else{

		if(mouse->tile != NULL){

			mouse->tile->is_hoover = SDL_FALSE;
			mouse->tile->is_pressed = SDL_FALSE;
		}
		mouse->tile = NULL;
	}
}

void check_who_pressed(Map *map, Mouse *mouse){

	SDL_bool found = SDL_FALSE;
	int x = 0;
	int y = 0;
	SDL_Rect mouse_pos = {mouse->position.x, mouse->position.y, 1, 1};

	while(found == SDL_FALSE && y < map->map_size_y && x < map->map_size_x){

		if(SDL_HasIntersection(&mouse_pos, &map->map[y][x].sprite.position)){

			mouse->index_tile_x = x;
			mouse->index_tile_y = y;
			found = SDL_TRUE;
		}

		y += 1;
		if(y == map->map_size_y){

			y = 0;
			x += 1;
		}
	}
}

void draw(SDL_Renderer *renderer, Tab_texture *tab_texture, Map map, Tab_text *tab_text){

	SDL_Color black = {0,0,0,255};
	set_color(renderer, black);
	SDL_RenderClear(renderer);

	draw_map(renderer, tab_texture, map);
	draw_text(renderer, tab_text);

	SDL_RenderPresent(renderer);
}