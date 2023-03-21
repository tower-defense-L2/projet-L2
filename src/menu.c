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
#include "../include/jeux.h"


int main(){
    pack_t * fenetre = NULL;
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Texture * texture_menu = NULL;
    bouton_t * bouton = NULL;
    bouton_t * bouton2 = NULL;
    Uint64 start, end;
    float elapsed = 0;
    SDL_Color couleurRouge = {255, 0, 0, 255};
    SDL_Color couleurNoire = {0, 0, 0, 255};
    Uint32 Click = 0; // état du clique
    int x = 0, y = 0; // position de la souris

    SDL_Rect win = {0, 0, 0, 0};
    SDL_Rect dst = {0, 0, 0, 0};
    /**
     * \brief Initialisation de la SDL avec gestion d'erreur
     */
    if(initilalisation_sdl()){
        return 1;
    }
    fenetre = creation_pack("menu tower defence", 854, 480, SDL_WINDOW_SHOWN, 30);
    if(fenetre == NULL){
        return 1;
    }
    SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
    if(load_bitmap("./ressources/menu.bmp", &texture_menu, fenetre)){
        return 1;
    }

    /**
     * \brief création des boutons et gestion d'erreur 
     */
    bouton = creation_bouton(fenetre, "Jouer", couleurRouge, couleurNoire, (win.w/4), (win.h/2));
    if(bouton == NULL){
        return 1;
    }
    bouton2 = creation_bouton(fenetre, "Quiter", couleurRouge, couleurNoire,
                    (bouton->dst.w + bouton->dst.x), (bouton->dst.h + bouton->dst.y));
    if(bouton2 == NULL){
        return 1;
    }


    SDL_PollEvent(&event);
    while(program_launched){
        /**
         * \brief debut du cronometre pour le temps d'execution de la boucle
         */
        start = SDL_GetPerformanceCounter();

        /**
         * \brief nettoyage du renderer
         */
        SDL_RenderClear(fenetre->renderer);

        /**
         * \brief recuperation de la taille de la fenetre et de la position de la souris
         */
        SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
        Click = SDL_GetMouseState(&x, &y);
        
        /**
         * \brief reinitialisation de la taille et de la position du rectangle de destination 
         */
        dst.h = 0; dst.w = 0; dst.x = 0; dst.y = 0;
        dst.w = win.w;
        dst.h = win.h;

        /**
         * \brief affichage de l'image de fond 
         */
        SDL_RenderCopy(fenetre->renderer, texture_menu, NULL, &dst);

        /**
         * \brief reposionnement des boutons et gestion de l'interaction avec la souris
         */
        position_bouton(bouton, (win.w/4), (win.h/2));
        if(gestion_bouton(bouton, fenetre, x, y)&& Click==SDL_BUTTON_LEFT){
            printf("on lance le jeu\n");
            jeux();
        }
        position_bouton(bouton2, (win.w/4), (4*win.h/7));
        if(gestion_bouton(bouton2, fenetre, x, y)&& Click==SDL_BUTTON_LEFT){
            program_launched = SDL_FALSE;
        }

        /**
         * \brief affichage du rendu
         */
        SDL_RenderPresent(fenetre->renderer);
        
        /**
         * \brief fin du cronometre et calcul du temps d'execution de la boucle
         */
        end = SDL_GetPerformanceCounter();
        elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();

        /**
         * \brief gestion des evenements et limitation de la boucle a 60 fps
         */
        SDL_WaitEventTimeout(&event, 1000/60 - elapsed);
        switch(event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                do {
                    SDL_PollEvent(&event);
                }while (event.type != SDL_MOUSEBUTTONUP);
                
                break;
        }
    }

    /**
     * \brief liberation de la memoire
     */
    SDL_DestroyTexture(texture_menu);
    texture_menu = NULL;
    supression_pack(&fenetre);
    supression_sdl();
    return 0;
}

