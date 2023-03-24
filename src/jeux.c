/**
 * \file jeux.c
 * \author meo (meo.prn@outlook.fr)
 * \brief boucle de jeu
 * \version 0.1.0
 * \date 2023-03-22
 * 
 * 
 */
#include "../include/jeux.h"

void jeux(){
    // création de la fenetre
    SDL_Rect win= {0,0,0,0};
    pack_t * fenetre = creation_pack("Jeu", 1600, 900, SDL_WINDOW_FULLSCREEN_DESKTOP |SDL_WINDOW_BORDERLESS, 30);
    /**
     * \brief verrouillage de la fenetre en plein écran 
     */
    SDL_SetWindowResizable(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowBordered(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowPosition(fenetre->fenetre, 0, 0);
    SDL_GetDisplayBounds(0,&win);
    SDL_SetWindowSize(fenetre->fenetre, win.w, win.h);

    // initialisation des variables
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Texture * texture = NULL;
    SDL_Texture * chemin = NULL;
    SDL_Texture * bordure = NULL;
    SDL_Texture * bille = NULL;
    SDL_Texture * tour = NULL;
    Uint64 start, end;
    float elapsed = 0;
    Uint32 Click = 0; // état du clique
    int x = 0, y = 0; // position de la souris
    SDL_Rect tuile= {0,0,0,0};
    
    // variable temporaire
    map_T map;

    for(int i = 0; i < HAUTEUR ; i++){
        for(int j = 0; j < LARGEUR; j++){
            map.cases[i][j]->type = VIDE;
        }
        map.cases[i][0]->type = CHEMIN;
        map.cases[i][LARGEUR-1]->type = CHEMIN;
        map.cases[i][1]->type = EMPLACEMENT;
    }

    // chargement de l'image de fond et gestion d'erreur
    if(load_bitmap("./ressources/font.bmp",&texture,fenetre)){
        return;
    }
    load_bitmap("./ressources/chemin.bmp",&chemin,fenetre);
    load_bitmap("./ressources/bordure.bmp",&bordure,fenetre);
    load_bitmap("./ressources/bille.bmp",&bille,fenetre);
    load_bitmap("./ressources/tour.bmp",&tour,fenetre);

    SDL_RenderCopy(fenetre->renderer,texture,NULL,NULL);
    SDL_RenderPresent(fenetre->renderer);
    SDL_RenderClear(fenetre->renderer);
    
    tuile = (SDL_Rect){0, 0, win.w/(LARGEUR+2), win.h/(HAUTEUR+2)};
    
    while(program_launched){
        SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
        start = SDL_GetPerformanceCounter();
        SDL_RenderClear(fenetre->renderer);
        Click = SDL_GetMouseState(&x, &y);
        SDL_RenderCopy(fenetre->renderer, texture, NULL, NULL);

        for(int j = 0; j < LARGEUR; j++){
            for(int i = 0; i < HAUTEUR; i++){
                tuile.y = (i+1) * tuile.h;
                tuile.x = (j+1) * tuile.w;
                switch(map.cases[i][j]->type){
                    case CHEMIN:
                        SDL_RenderCopy(fenetre->renderer, chemin, NULL, &tuile);
                        break;
                    case EMPLACEMENT:
                        SDL_RenderCopy(fenetre->renderer, bordure, NULL, &tuile);
                        break;
                    case VIDE:
                        SDL_RenderCopy(fenetre->renderer, chemin, NULL, &tuile);
                        SDL_RenderCopy(fenetre->renderer, bille, NULL, &tuile);
                        break;
                }
            }
        }
        SDL_RenderPresent(fenetre->renderer);
        end = SDL_GetPerformanceCounter();
        elapsed = (end - start) * 1000 / (float)SDL_GetPerformanceFrequency();
        if(elapsed < 1000/60){
            SDL_Delay((1000/60) - elapsed);
        }
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        program_launched = SDL_FALSE;
                        break;
                }
                break;
        }
    }
    
    SDL_Delay(5000);

    // destruction de la texture
    SDL_DestroyTexture(texture);
    texture = NULL;

    // fermeture de la fenetre de jeu
    supression_pack(&fenetre);
}