/*
Auteur Gautier Levesque
09/06/2022
*/

#ifndef __INPUT_H__
#define __INPUT_H__

#include "mouse.h"

/*structure pour la gestion des inputs*/
typedef struct input{

	SDL_bool a,z,e,r,t,y,u,i,o,p,q,s,d,f,g,h,j,k,l,m,w,x,c,v,b,n,space;
}Input;

/*initialisation de l'input*/
Input init_input(void);

/*update des inputs*/
SDL_bool update_input(Input *input, Mouse *mouse);

#endif