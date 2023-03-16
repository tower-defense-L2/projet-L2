/**
 * \file menu.c
 * \author meo (meo.prn@outlook.fr)
 * \brief menu principal du jeu
 * \version 0.1.0
 * \date 2023-03-16
 * 
 */
#include "../include/init_supr_sdl.h"

int menu(){
    fenetre_t * fenetre = malloc(sizeof(fenetre_t));
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    texture_t * texture_menu = malloc(sizeof(texture_t));
    Uint64 start, end;
    float elapsed;

    SDL_Rect win = {0, 0, 0, 0};
    SDL_Rect dst = {0, 0, 0, 0};

    /**
     * \brief Initialisation de la SDL avec gestion d'erreur
     */
    if(intilalisation_sdl(fenetre)){
        return 1;
    }
    if(load_bitmap("./ressources/menu.bmp", texture_menu, fenetre)){
        return 1;
    }

    while(program_launched){
        start = SDL_GetPerformanceCounter();
        SDL_RenderClear(fenetre->renderer);

        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            default:
                dst.h = 0; dst.w = 0; dst.x = 0; dst.y = 0;
                SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
                dst.w = win.w;
                dst.h = win.h;
                SDL_RenderCopy(fenetre->renderer, texture_menu->texture, NULL, &dst);
                SDL_RenderPresent(fenetre->renderer);
                break;
        }
        end = SDL_GetPerformanceCounter();
        elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(1000/60 - elapsed);
    }
    supression_texture_liste(texture_menu);
    supression_sdl(fenetre);
}

void main(){
    menu();
}