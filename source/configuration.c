/*
Auteur Gautier Levesque
06/06/2022
*/

#include "configuration.h"

void save_configuration_file(Configuration configuration){

	FILE *file = fopen(configuration.path, "w");
	if(file == NULL){

		perror("fopen failed");
		exit(1);
	}

	fprintf(file, "titre=%s\n", &configuration.title);
	fprintf(file, "window_width=%d\n", configuration.window_width);
	fprintf(file, "window_height=%d\n", configuration.window_height);
	fprintf(file, "window_pos_x=%d\n", configuration.window_pos_x);
	fprintf(file, "window_pos_y=%d\n", configuration.window_pos_y);
	fprintf(file, "window_flag=%d\n", configuration.flag_window);
	fprintf(file, "renderer_flag=%d\n", configuration.flag_renderer);

	fclose(file);
	file = NULL;
}

Configuration load_configuration_file(const char *path){

	assert(path != NULL);

	FILE *file = fopen(path, "r");

	if(file == NULL){

		creat_configuration_file(path);
	}

	file = fopen(path, "r");
	if(file == NULL){

		perror("fopen failed");
		exit(1);
	}
	Configuration configuration;

	configuration.path = malloc(sizeof(char) * (strlen(path) + 1));
	if(configuration.path == NULL){

		perror("malloc failed");
		exit(1);
	}

	strcpy(configuration.path, path);

	fscanf(file, "titre=%s\n", &configuration.title);
	configuration.title[strlen(configuration.title)] = '\0';

	fscanf(file, "window_width=%d\n", &configuration.window_width);
	fscanf(file, "window_height=%d\n", &configuration.window_height);
	fscanf(file, "window_pos_x=%d\n", &configuration.window_pos_x);
	fscanf(file, "window_pos_y=%d\n", &configuration.window_pos_y);
	fscanf(file, "window_flag=%d\n", &configuration.flag_window);
	fscanf(file, "renderer_flag=%d\n", &configuration.flag_renderer);

	fclose(file);
	file = NULL;

	return configuration;
}

void creat_configuration_file(const char *path){

	assert(path != NULL);

	creat_arborescence(path);

	FILE *file = fopen(path, "w");
	if(file == NULL){

		perror("fopen failed");
		exit(1);
	}

	fprintf(file, "%s\n", "titre=test_window");
	fprintf(file, "%s\n", "window_width=800");
	fprintf(file, "%s\n", "window_height=600");
	fprintf(file, "%s\n", "window_pos_x=0");
	fprintf(file, "%s\n", "window_pos_y=0");
	fprintf(file, "%s\n", "window_flag=0");
	fprintf(file, "%s\n", "renderer_flag=0");

	fclose(file);
	file = NULL;
}