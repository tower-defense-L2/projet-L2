/**
 * \file menu.c
 * \author meo (meo.prn@outlook.fr)
 * \brief menu principal du jeu
 * \version 0.1.0
 * \date 2023-03-16
 * 
 */
#include "../include/init_supr_sdl.h"

void menu(){
    pack_t * fenetre = malloc(sizeof(pack_t));
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    texture_t * texture_menu = malloc(sizeof(texture_t));
    Uint64 start, end;
    float elapsed;
    SDL_Surface *menu[2] = {NULL};
    SDL_Color couleurRouge = {255, 0, 0};

    SDL_Rect win = {0, 0, 0, 0};
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Rect bouton = {0, 0, 0, 0};

    /**
     * \brief Initialisation de la SDL avec gestion d'erreur
     */
    if(intilalisation_sdl()){
        return;
    }
    if(creation_pack(fenetre, "Menu Tower Defense")){
        return;
    }
    if(load_bitmap("./ressources/menu.bmp", texture_menu, fenetre)){
        return;
    }

    menu[0] = TTF_RenderText_Blended(fenetre->police, "Jouer", couleurRouge);
    menu[1] = TTF_RenderText_Blended(fenetre->police, "Quiter", couleurRouge);

    while(program_launched){
        start = SDL_GetPerformanceCounter();
        SDL_RenderClear(fenetre->renderer);
        SDL_WaitEventTimeout(&event, 1000/60 - elapsed);
        SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);

        switch(event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){  
                    do{
                        SDL_WaitEvent(&event);
                    } while (event.type != SDL_MOUSEBUTTONUP);
                    
                    if(event.button.button == SDL_BUTTON_LEFT){
                        if(event.button.x > win.x && event.button.x < win.h && event.button.y > win.y && event.button.y < win.w){
                            supression_texture_liste(texture_menu);
                            load_bitmap("./ressources/test/font2.bmp", texture_menu, fenetre);
                        }
                    }
                }
                break;
        }
        
        
        dst.h = 0; dst.w = 0; dst.x = 0; dst.y = 0;
        dst.w = win.w;
        dst.h = win.h;
        SDL_RenderCopy(fenetre->renderer, texture_menu->texture, NULL, &dst);
        SDL_RenderPresent(fenetre->renderer);
        
        end = SDL_GetPerformanceCounter();
        elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    }
    supression_texture_liste(texture_menu);
    supression_sdl(fenetre);
}

void main(){
    menu();
}