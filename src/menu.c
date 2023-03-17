/**
 * \file menu.c
 * \author meo (meo.prn@outlook.fr)
 * \brief menu principal du jeu
 * \version 0.1.0
 * \date 2023-03-16
 * 
 */
#include "../include/init_supr_sdl.h"
#include "../include/interaction_souris.h"
#include "../include/struct_sdl.h"


int main(){
    pack_t * fenetre = malloc(sizeof(pack_t));
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Texture * texture_menu = NULL;
    bouton_t * bouton = NULL;
    bouton_t * bouton2 = NULL;
    Uint64 start, end;
    float elapsed = 0;
    SDL_Color couleurRouge = {255, 0, 0};
    SDL_Color couleurNoire = {0, 0, 0};
    Uint32 Click = 0; // état du clique
    int x = 0, y = 0; // position de la souris

    SDL_Rect win = {0, 0, 0, 0};
    SDL_Rect dst = {0, 0, 0, 0};
    /**
     * \brief Initialisation de la SDL avec gestion d'erreur
     */
    if(intilalisation_sdl()){
        return;
    }
    if(creation_pack(fenetre, "Menu Tower Defense")){
        return;
    }
    SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
    if(load_bitmap("./ressources/menu.bmp", &texture_menu, fenetre)){
        return;
    }

    bouton = creation_bouton(fenetre, "Jouer", couleurRouge, couleurNoire, (win.w/4), (win.h/2));
    bouton2 = creation_bouton(fenetre, "Quiter", couleurRouge, couleurNoire, (win.w/4), (4*win.h/7));

    SDL_PollEvent(&event);
    while(program_launched){
        SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
        start = SDL_GetPerformanceCounter();
        SDL_RenderClear(fenetre->renderer);
        Click = SDL_GetMouseState(&x, &y);
        
        
        dst.h = 0; dst.w = 0; dst.x = 0; dst.y = 0;
        dst.w = win.w;
        dst.h = win.h;
        SDL_RenderCopy(fenetre->renderer, texture_menu, NULL, &dst);

        position_bouton(bouton, (win.w/4), (win.h/2));
        if(gestion_bouton(bouton, fenetre, x, y)&& Click==SDL_BUTTON_LEFT){
            printf("on lance le jeu\n");
        }
        position_bouton(bouton2, (win.w/4), (4*win.h/7));
        if(gestion_bouton(bouton2, fenetre, x, y)&& Click==SDL_BUTTON_LEFT){
            program_launched = SDL_FALSE;
        }

        
        SDL_RenderPresent(fenetre->renderer);
        
        
        SDL_WaitEventTimeout(&event, 1000/60 - elapsed);
        switch(event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                do {
                    SDL_WaitEventTimeout(&event, 100);
                }while (event.type != SDL_MOUSEBUTTONUP);
                
                break;
        }

        end = SDL_GetPerformanceCounter();
        elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    }
    SDL_DestroyTexture(texture_menu);
    texture_menu = NULL;
    supression_pack(&fenetre);
    supression_sdl();
    return 0;
}

