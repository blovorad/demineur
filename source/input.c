/*
Auteur Gautier Levesque
09/06/2022
*/

#include "input.h"

Input init_input(void){

	Input input = {SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, 
				   SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, 
				   SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE, SDL_FALSE};

	return input;
}

SDL_bool update_input(Input *input, Mouse *mouse){

	SDL_Event event;

	while(SDL_PollEvent(&event)){

		switch(event.type){

			case SDL_QUIT:
				return SDL_FALSE;

			case SDL_MOUSEBUTTONDOWN:

				switch(event.button.button){

					case SDL_BUTTON_LEFT:
						mouse->left_click = event.button.state;
						break;
					case SDL_BUTTON_RIGHT:
						mouse->right_click = event.button.state;
						break;

					default:
						break;
				}
				break;

			case SDL_MOUSEBUTTONUP:

				switch(event.button.button){

					case SDL_BUTTON_LEFT:
						mouse->left_click = event.button.state;
						mouse->old_left_click = !event.button.state;
						break;
					case SDL_BUTTON_RIGHT:
						mouse->right_click = event.button.state;
						mouse->old_right_click = !event.button.state;
						break;

					default:
						break;
				}
				break;

			case SDL_KEYDOWN:

				switch(event.key.keysym.sym){

					case SDLK_a:
						input->a = event.key.state;
						break;
					case SDLK_z:
						input->z = event.key.state;
						break;
					case SDLK_e:
						input->e = event.key.state;
						break;
					case SDLK_r:
						input->r = event.key.state;
						break;
					case SDLK_t:
						input->t = event.key.state;
						break;
					case SDLK_y:
						input->y = event.key.state;
						break;
					case SDLK_u:
						input->u = event.key.state;
						break;
					case SDLK_i:
						input->i = event.key.state;
						break;
					case SDLK_o:
						input->o = event.key.state;
						break;
					case SDLK_p:
						input->p = event.key.state;
						break;
					case SDLK_q:
						input->q = event.key.state;
						break;
					case SDLK_s:
						input->s = event.key.state;
						break;
					case SDLK_d:
						input->d = event.key.state;
						break;
					case SDLK_f:
						input->f = event.key.state;
						break;
					case SDLK_g:
						input->g = event.key.state;
						break;
					case SDLK_h:
						input->h = event.key.state;
						break;
					case SDLK_j:
						input->j = event.key.state;
						break;
					case SDLK_k:
						input->k = event.key.state;
						break;
					case SDLK_l:
						input->l = event.key.state;
						break;
					case SDLK_m:
						input->m = event.key.state;
						break;
					case SDLK_w:
						input->w = event.key.state;
						break;
					case SDLK_x:
						input->x = event.key.state;
						break;
					case SDLK_c:
						input->c = event.key.state;
						break;
					case SDLK_v:
						input->v = event.key.state;
						break;
					case SDLK_b:
						input->b = event.key.state;
						break;
					case SDLK_n:
						input->n = event.key.state;
						break;
					case SDLK_SPACE:
						input->space = event.key.state;
						break;

					default:
						break;
				}
				break;

			case SDL_KEYUP:

				switch(event.key.keysym.sym){

					case SDLK_a:
						input->a = event.key.state;
						break;
					case SDLK_z:
						input->z = event.key.state;
						break;
					case SDLK_e:
						input->e = event.key.state;
						break;
					case SDLK_r:
						input->r = event.key.state;
						break;
					case SDLK_t:
						input->t = event.key.state;
						break;
					case SDLK_y:
						input->y = event.key.state;
						break;
					case SDLK_u:
						input->u = event.key.state;
						break;
					case SDLK_i:
						input->i = event.key.state;
						break;
					case SDLK_o:
						input->o = event.key.state;
						break;
					case SDLK_p:
						input->p = event.key.state;
						break;
					case SDLK_q:
						input->q = event.key.state;
						break;
					case SDLK_s:
						input->s = event.key.state;
						break;
					case SDLK_d:
						input->d = event.key.state;
						break;
					case SDLK_f:
						input->f = event.key.state;
						break;
					case SDLK_g:
						input->g = event.key.state;
						break;
					case SDLK_h:
						input->h = event.key.state;
						break;
					case SDLK_j:
						input->j = event.key.state;
						break;
					case SDLK_k:
						input->k = event.key.state;
						break;
					case SDLK_l:
						input->l = event.key.state;
						break;
					case SDLK_m:
						input->m = event.key.state;
						break;
					case SDLK_w:
						input->w = event.key.state;
						break;
					case SDLK_x:
						input->x = event.key.state;
						break;
					case SDLK_c:
						input->c = event.key.state;
						break;
					case SDLK_v:
						input->v = event.key.state;
						break;
					case SDLK_b:
						input->b = event.key.state;
						break;
					case SDLK_n:
						input->n = event.key.state;
						break;
					case SDLK_SPACE:
						input->space = event.key.state;
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}

	return SDL_TRUE;
}