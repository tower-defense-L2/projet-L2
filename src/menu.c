/**
 * \file menu.c
 * \author meo (meo.prn@outlook.fr)
 * \brief menu principal du jeu
 * \version 0.1.0
 * \date 2023-03-16
 * 
 */
#include "../include/menu.h"

/**
 * \brief fonction de reformattage de la fenetre en fenetre de menu
 * 
 * \param fenetre pointeur sur la structure pack_t
 * \param win pointeur sur la structure SDL_Rect
 */
static
void modelage_fenetre_menu(pack_t * fenetre, SDL_Rect * win){
    SDL_SetWindowBordered(fenetre->fenetre, SDL_TRUE);
    SDL_SetWindowResizable(fenetre->fenetre, SDL_TRUE);
    SDL_SetWindowFullscreen(fenetre->fenetre, 0);
    SDL_SetWindowSize(fenetre->fenetre, 854, 480);
    SDL_SetWindowPosition(fenetre->fenetre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    
    SDL_GetDisplayBounds(0,win);
}

extern
int menu(){
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
    

    // création de la fenetre
    fenetre = creation_pack(TITRE, 854, 480, SDL_WINDOW_SHOWN, 30);
    if(fenetre == NULL){
        return 1;
    }
    modelage_fenetre_menu(fenetre, &win);
    SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
    if(load_bitmap("menu", &texture_menu, fenetre)){
        return 1;
    }


    // création des boutons et gestion d'erreur 
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
    //boucle principale du programme
    while(program_launched){
        // debut du cronometre pour le temps d'execution de la boucle
        start = SDL_GetPerformanceCounter();

        // nettoyage du renderer
        SDL_RenderClear(fenetre->renderer);

        // recuperation de la taille de la fenetre et de la position de la souris
        SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
        Click = SDL_GetMouseState(&x, &y);
        
        // reinitialisation de la taille et de la position du rectangle de destination 
        dst.h = 0; dst.w = 0; dst.x = 0; dst.y = 0;
        dst.w = win.w;
        dst.h = win.h;

        // affichage de l'image de fond 
        SDL_RenderCopy(fenetre->renderer, texture_menu, NULL, &dst);

        // reposionnement des boutons et gestion de l'interaction avec la souris
        position_bouton(bouton, (win.w/4), (win.h/2));
        if(gestion_bouton(bouton, fenetre, x, y)&& Click==SDL_BUTTON_LEFT){

            // lancement du jeu
            jeux(fenetre);

            // refomatage de la fenetre
            modelage_fenetre_menu(fenetre, &win);
        }
        position_bouton(bouton2, (win.w/4), (4*win.h/7));
        if(gestion_bouton(bouton2, fenetre, x, y)&& Click==SDL_BUTTON_LEFT){
            program_launched = SDL_FALSE;
        }

        // affichage du rendu
        SDL_RenderPresent(fenetre->renderer);
        
        // fin du cronometre et calcul du temps d'execution de la boucle
        end = SDL_GetPerformanceCounter();
        elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();

        // gestion des evenements et limitation de la boucle a 60 fps
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
    // fin de boucle principale du programme

    // liberation de la memoire
    SDL_DestroyTexture(texture_menu);
    texture_menu = NULL;
    supression_pack(&fenetre);
    return 0;
}