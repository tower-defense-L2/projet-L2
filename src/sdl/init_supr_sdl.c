#include "../../include/init_supr_sdl.h"



int intilalisation_sdl(fenetre_t * fenetre){
    /**
     * \brief Initialisation de la SDL avecc gestion d'erreur
     * 
     */
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }


    /**
     * \brief Création de la fenêtre
     */
    fenetre->fenetre = SDL_CreateWindow("test_SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_RESIZABLE);
    /**
     * \brief Gestion d'erreur de la fenêtre
     */
    if(fenetre->fenetre == NULL){ 
        printf("Erreur de création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /** 
     * \brief création du renedrer
     */
    fenetre->renderer = SDL_CreateRenderer(fenetre->fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    /**
     * \brief gestion d'erreur du renderer
     */
    

    if(fenetre->renderer == NULL){
        printf("Erreur de création du renderer : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }
    return 0;
}


void supression_sdl(fenetre_t * fenetre){
    /**
     * \brief Supression de la fenêtre
     */
    SDL_DestroyWindow(fenetre->fenetre);
    /**
     * \brief Supression du renderer
     */
    SDL_DestroyRenderer(fenetre->renderer);
    /**
     * \brief Quitte la SDL
     */
    SDL_Quit();
}




int load_bitmap(char *path, texture_t *texture, fenetre_t * fenettre){
    SDL_Surface * fond = NULL;
    /**
     * \brief load de la bitmap
     */
    fond = SDL_LoadBMP(path);
    /**
     * \brief gestion d'erreur du load
     */
    if(fond == NULL){
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /**
     * \brief création de la texture
     */
    texture->texture = SDL_CreateTextureFromSurface(fenettre->renderer, fond);
    /**
     * \brief gestion d'erreur de la texture
     */
    if(texture->texture == NULL){
        printf("Erreur de création de la texture : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /**
     * \brief libération de la surface
     */
    SDL_FreeSurface(fond);
    return 0;
}

void supression_texture(texture_t * texture){
    /**
     * \brief Supression de la texture
     */
    SDL_DestroyTexture(texture->texture);
    if(texture->precedent != NULL){
        texture->precedent->suivant = texture->suivant;
    }
    if(texture->suivant != NULL){
        texture->suivant->precedent = texture->precedent;
    }
    free(texture);
    texture = NULL;
}

void supression_texture_list(texture_t * texture){
    /**
     * \brief Supression de la texture
     */
    if(texture->suivant != NULL){
        supression_texture_list(texture->suivant);
    }
    supression_texture(texture);
}