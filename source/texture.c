/*
Auteur Gautier Levesque
07/06/2022
*/

#include "texture.h"

Tab_texture creat_tab_texture(const char *path){

	assert(path != NULL);

	Tab_texture tab_texture = {0, NULL};

	const char *extension[] = {".png"}; 
	File_file_tq file = get_all_path_file_s(path, extension, 1);

	if(file.tete != NULL){

		tab_texture.nb_texture = count_nb_texture(file);
		tab_texture.textures = malloc(sizeof(Texture) * tab_texture.nb_texture);
		if(tab_texture.textures == NULL){

			perror("malloc failed");
			exit(1);
		}

		int i = 0;
		while(file.tete != NULL){

			tab_texture.textures[i].path = malloc(sizeof(char) * (strlen(file.tete->name) + 1));
			if(tab_texture.textures[i].path == NULL){

				perror("malloc failed");
				exit(1);
			}

			strcpy(tab_texture.textures[i].path, file.tete->name);

			supp_tete_fd(&file);
			i+= 1;
		}	
		for(int i = 0; i < tab_texture.nb_texture; i++){

			tab_texture.textures[i].current_use = 0;
			tab_texture.textures[i].texture = NULL;
		}
	}

	return tab_texture;
}

int count_nb_texture(File_file_tq file){

	int nb_texture = 0;

	while(file.tete != NULL){

		nb_texture += 1;
		file.tete = file.tete->suivant;
	}

	return nb_texture;
}

SDL_Texture *creat_texture(SDL_Renderer *renderer, const char *path){

	assert(renderer != NULL);
	assert(path != NULL);

	SDL_Surface *surface = IMG_Load(path);
	if(surface == NULL){

		SDL_Log("IMG_Load failed: %s\n", IMG_GetError());
		exit(1);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = NULL;
	if(texture == NULL){

		SDL_Log("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}

	return texture;
}

SDL_Texture *get_texture(Tab_texture *tab_texture, const int index){

	assert(tab_texture != NULL);
	assert(index >= 0 && index < tab_texture->nb_texture);

	if(index >= 0 && index < tab_texture->nb_texture){

		return tab_texture->textures[index].texture;
	}

	return NULL;
}

int get_index_texture(SDL_Renderer *renderer, Tab_texture *tab_texture, const char *path){

	assert(renderer != NULL);
	assert(tab_texture != NULL);
	assert(path != NULL);

	int index = -1;
	int i = 0;

	while(index == -1 && i < tab_texture->nb_texture){

		if(strcmp(path, tab_texture->textures[i].path) == 0){

			index = i;
			if(tab_texture->textures[i].current_use == 0){

				tab_texture->textures[i].texture = creat_texture(renderer, tab_texture->textures[i].path);
			}
			tab_texture->textures[i].current_use += 1;
		}
		i += 1;
	}

	return index;
}

void remove_current_use_texture(Tab_texture *tab_texture, const int index){

	assert(tab_texture != NULL);
	assert(index >= 0 && index < tab_texture->nb_texture);

	if(index >= 0 && index < tab_texture->nb_texture){

		tab_texture->textures[index].current_use -= 1;
		if(tab_texture->textures[index].current_use < 1){

			destroy_texture(tab_texture, index);
		}
	}
}

void destroy_texture(Tab_texture *tab_texture, const int index){

	assert(tab_texture != NULL);
	assert(index >= 0 && index < tab_texture->nb_texture);

	if(index >= 0 && index < tab_texture->nb_texture){

		tab_texture->textures[index].current_use = 0;
		if(tab_texture->textures[index].texture != NULL){

			SDL_DestroyTexture(tab_texture->textures[index].texture);
			tab_texture->textures[index].texture = NULL;
		}
	}
}