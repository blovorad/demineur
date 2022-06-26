/*
Auteur Gautier Levesque
06/06/2022
*/

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "directory.h"

/*pour les uint32_t, test pour SDL, pour cela qu'il y a ça*/
#include <stdint.h>

/*structure de sauvegarde d'une configuration*/
typedef struct configuration{

	char *path;
	char title[255];
	int window_width;
	int window_height;
	int window_pos_x;
	int window_pos_y;
	uint32_t flag_window;
	uint32_t flag_renderer;
}Configuration;

/*creation d'un fichier de configuration standard*/
void creat_configuration_file(const char *path);

/*sauvgarde d'un fichier de configuration*/
void save_configuration_file(Configuration configuration);

/*chargement d'un fichier de configuration*/
Configuration load_configuration_file(const char *path);

#endif