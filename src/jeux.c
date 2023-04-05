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

#include "../test/deff.h"

/**
 * \brief fonction qui passe la fenetre en plein écran
 * 
 * \param fenetre pointeur sur le pack_t de la fenetre
 * \param win pointeur sur la SDL_Rect de la fenetre
 */
static
void plein_ecran(pack_t * fenetre, SDL_Rect * win){
    SDL_SetWindowFullscreen(fenetre->fenetre, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetWindowBordered(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowResizable(fenetre->fenetre, SDL_FALSE);
    SDL_GetDisplayBounds(0,win);
}

/**
 * \brief fonction qui passe la fenetre en fenétrée
 * 
 * \param fenetre pointeur sur le pack_t de la fenetre
 * \param win pointeur sur la SDL_Rect de la fenetre
 */
static
void fenetree(pack_t * fenetre, SDL_Rect * win){
    SDL_SetWindowBordered(fenetre->fenetre, SDL_TRUE);
    SDL_SetWindowResizable(fenetre->fenetre, SDL_TRUE);
    SDL_SetWindowFullscreen(fenetre->fenetre, 0);
    SDL_SetWindowSize(fenetre->fenetre,1600,900);
    SDL_SetWindowMinimumSize(fenetre->fenetre,854,480);
    *win = (SDL_Rect){0,0,0,0};
    SDL_GetWindowSize(fenetre->fenetre,&win->w,&win->h);
}



extern
int jeux(pack_t * fenetre){
    // création de la fenetre
    SDL_Rect win= {0,0,0,0};
    // transformation de la fenetre en fenetre de jeu
    plein_ecran(fenetre, &win);
    

    // initialisation des variables
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    Uint64 start, end;
    float elapsed = 0;
    Uint32 Click = 0; // état du clique
    int x = 0, y = 0; // position de la souris
    SDL_bool est_plein_ecran = SDL_TRUE;
    char * info= malloc(sizeof(char)*30);

    // initialisation des textures
    SDL_Texture * texture = NULL;
    SDL_Texture * chemin = NULL;
    SDL_Texture * bordure = NULL;
    SDL_Texture * vide = NULL;
    bitexture_t * emplacement = NULL;
    SDL_Texture * enemie = NULL;
    SDL_Texture * tour = NULL;
    // texture de texte
    SDL_Texture * quiter = NULL;
    SDL_Texture * argent = NULL;
    SDL_Texture * vie = NULL;
    
    // initialisation des rectangles
    SDL_Rect tuile= {0,0,0,0};
    SDL_Rect quiter_rect = {0,0,0,0};
    SDL_Rect argent_rect = {0,0,0,0};
    SDL_Rect vie_rect = {0,0,0,0};
    
    // initialisaion des couleurs
    SDL_Color couleur_blanc = {255,255,255,255};
    SDL_Color couleur_doree = {255,215,0,255};
    SDL_Color couleur_rouge = {255,0,0,255};
        
    // variable temporaire
        map = malloc(sizeof(map_T) + sizeof(case_T*) * HAUTEUR);
        for(int i = 0; i < HAUTEUR ; i++){
            for(int j = 0; j < LARGEUR; j++){
                map->cases[i][j] = malloc(sizeof(case_T));
                map->cases[i][j]->type = VIDE;
            }
        }
        map->cases[0][0]->type = CHEMIN;
        map->cases[0][0]->case_pl.chemin.enemi = NULL;
        map->cases[0][1]->type = CHEMIN;
        map->cases[0][1]->case_pl.chemin.enemi = malloc(sizeof(ennemi_T));
        map->cases[1][0]->type = EMPLACEMENT;
        map->cases[1][0]->case_pl.emplacement.tour = NULL;
        map->cases[1][1]->type = EMPLACEMENT;
        map->cases[1][1]->case_pl.emplacement.tour = malloc(sizeof(tour_T));

        joueur = malloc(sizeof(joueur_T));
        joueur->argent = 100;
        joueur->vie = 100;
    


    // chargement de l'image de fond et gestion d'erreur
    if(load_bitmap("font",&texture,fenetre)){
        return 1;
    }
    if(load_bitmap("chemin",&chemin,fenetre)){
        return 1;
    }
    if(load_bitmap("bordure",&bordure,fenetre)){
        return 1;
    }
    if(load_bitmap("bille",&enemie,fenetre)){
        return 1;
    }
    if(load_bitmap("tour",&tour,fenetre)){
        return 1;
    }
    if(load_bitmap("vide",&vide,fenetre)){
        return 1;
    }
    quiter = creation_texte(fenetre, "Esc : quiter le jeu  F11 : plein ecran", couleur_blanc);
    if (quiter == NULL){
        return 1;
    }
    SDL_QueryTexture(quiter, NULL, NULL, &quiter_rect.w, &quiter_rect.h);
    emplacement = creation_bitexture(fenetre, "bordure", "bordure_survol", 0, 0);
    if (emplacement == NULL){
        return 1;
    }

    SDL_RenderCopy(fenetre->renderer,texture,NULL,NULL);
    SDL_RenderPresent(fenetre->renderer);
    SDL_RenderClear(fenetre->renderer);
    
    
    
    while(program_launched){
        // la taille de la fenetre est mise a jour
        SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
        start = SDL_GetPerformanceCounter();

        // la taille des tuile est calculer en fonction de la fenettre
        tuile = (SDL_Rect){0, 0, win.w/(LARGEUR+2), win.h/(HAUTEUR+2)};

        SDL_RenderClear(fenetre->renderer);
        Click = SDL_GetMouseState(&x, &y);

        // affichage du fond
        SDL_RenderCopy(fenetre->renderer, texture, NULL, NULL);


        // affichage menu
        SDL_RenderCopy(fenetre->renderer, quiter, NULL, &quiter_rect);

           
        // creation des texte d'information
        sprintf(info, "%d", joueur->vie);
        strcat(info," : pv");
        vie = creation_texte(fenetre, info, couleur_rouge);
        SDL_QueryTexture(vie, NULL, NULL, &vie_rect.w, &vie_rect.h);
        vie_rect.x = win.w - vie_rect.w;

        sprintf(info, "%d", joueur->argent);
        strcat(info, " : or");
        argent = creation_texte(fenetre, info, couleur_doree);
        SDL_QueryTexture(argent, NULL, NULL, &argent_rect.w, &argent_rect.h);
        argent_rect.x = win.w - argent_rect.w - vie_rect.w - 30;

        SDL_RenderCopy(fenetre->renderer, vie, NULL, &vie_rect);
        SDL_RenderCopy(fenetre->renderer, argent, NULL, &argent_rect);
        SDL_DestroyTexture(vie);
        SDL_DestroyTexture(argent);
        vie = NULL;
        argent = NULL;

     
        
        
        // affichage des tuiles
        for(int j = 0; j < LARGEUR; j++){
            for(int i = 0; i < HAUTEUR; i++){
                // calcul de la position de la tuile suivante
                tuile.y = (i+1) * tuile.h;
                tuile.x = (j+1) * tuile.w;

                // selection de la texture a afficher
                switch(map->cases[i][j]->type){
                    case CHEMIN:
                        SDL_RenderCopy(fenetre->renderer, chemin, NULL, &tuile);
                        if(map->cases[i][j]->case_pl.chemin.enemi != NULL){
                            SDL_RenderCopy(fenetre->renderer, enemie, NULL, &tuile);
                        }
                        break;
                    case EMPLACEMENT:
                        // gestion des textures multiples
                        if(map->cases[i][j]->case_pl.emplacement.tour != NULL){
                            SDL_RenderCopy(fenetre->renderer, bordure, NULL, &tuile);
                            SDL_RenderCopy(fenetre->renderer, tour, NULL, &tuile);
                        }
                        else{
                            emplacement->dst = tuile;
                            gestion_bitexture(emplacement, fenetre, x, y);
                        }
                        break;
                    case VIDE:
                        SDL_RenderCopy(fenetre->renderer, vide, NULL, &tuile);
                        break;
                }
            }
        }
        // gestion du survol


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
                    case SDLK_F11:
                        if(est_plein_ecran){
                            fenetree(fenetre, &win);
                            est_plein_ecran = SDL_FALSE;
                        }
                        else{
                            plein_ecran(fenetre, &win);
                            est_plein_ecran = SDL_TRUE;
                        }
                        
                }
                break;
        }
    }


    // destruction de la texture
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(quiter);
    SDL_DestroyTexture(chemin);
    SDL_DestroyTexture(bordure);
    SDL_DestroyTexture(enemie);
    SDL_DestroyTexture(tour);
    SDL_DestroyTexture(emplacement->normale);
    SDL_DestroyTexture(emplacement->survol);
    free(emplacement);
    free(info);
    emplacement = NULL;
    texture = NULL;
    chemin = NULL;
    bordure = NULL;
    enemie = NULL;
    tour = NULL;
    return 0;
}