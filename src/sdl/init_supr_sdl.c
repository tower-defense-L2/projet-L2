/**
 * \file init_supr_sdl.c
 * \author meo (meo.prn@outlook.fr)
 * \brief source des fonctions servant pour la création et la destruction de la sdl
 * \version 0.1.0
 * \date 2023-03-22
 * 
 * 
 */
#include "../../include/init_supr_sdl.h"

pack_t * creation_pack(char * titre, int width, int height, int flags, int taille_police){
    pack_t * fenetre = malloc(sizeof(pack_t));

    /**
     * \brief Création de la fenêtre
     */
    fenetre->fenetre = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    /**
     * \brief Gestion d'erreur de la fenêtre
     */
    if(fenetre->fenetre == NULL){ 
        printf("Erreur de création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        return NULL;
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
        return NULL;
    }

    /**
     * \brief creation de la police
     */
    fenetre->police = TTF_OpenFont("./ressources/arial.ttf", taille_police);
    /**
     * \brief gestion d'erreur de la police
     */
    if(fenetre->police == NULL){
        printf("Erreur de création de la police : %s", TTF_GetError());
        SDL_Quit();
        return NULL;
    }

    return fenetre;
}

int initilalisation_sdl(){
    /**
     * \brief Initialisation de la SDL avecc gestion d'erreur
     * 
     */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }
    /**
     * \brief Initialisation de SDL_ttf avec gestion d'erreur
     */
    if(TTF_Init() < 0){
        printf("Erreur d'initialisation de SDL_ttf : %s", TTF_GetError());
        SDL_Quit();
        return 1 ;
    }
    return 0;
}


void supression_pack(pack_t ** fenetre){
    /**
     * \brief Supression de la police
     */
    TTF_CloseFont((*fenetre)->police);
    /**
     * \brief Supression du renderer
     */
    SDL_DestroyRenderer((*fenetre)->renderer);
    /**
     * \brief Supression de la fenêtre
     */
    SDL_DestroyWindow((*fenetre)->fenetre);
    free(*fenetre);
    *fenetre = NULL;
}

void supression_sdl(){
    /**
     * \brief Quitte SDL_ttf
     */
    TTF_Quit();
    /**
     * \brief Quitte la SDL
     */
    SDL_Quit();
}


int load_bitmap(const char *path, SDL_Texture ** texture, pack_t * fenettre){
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
    *texture = SDL_CreateTextureFromSurface(fenettre->renderer, fond);
    /**
     * \brief gestion d'erreur de la texture
     */
    if(*texture == NULL){
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
    /**
     * \brief reatribution des pointeurs de la liste
     */
    if(texture->precedent != NULL){
        texture->precedent->suivant = texture->suivant;
    }
    if(texture->suivant != NULL){
        texture->suivant->precedent = texture->precedent;
    }
    /**
     * \brief destruction de la texture et libération de la mémoire
     */
    free(texture);
    texture = NULL;
}

void supression_texture_liste(texture_t * texture){
    /**
     * \brief Supression de la liste de texture en récursivité
     */
    if(texture->suivant != NULL){
        supression_texture_liste(texture->suivant);
    }
    /**
     * \brief supression de la texture actuelle
     */
    supression_texture(texture);
}


bouton_t * creation_bouton(pack_t * fenetre, char * texte,
                SDL_Color couleur, SDL_Color wrap, int x, int y){
    
    bouton_t * bouton = malloc(sizeof(bouton_t));
    SDL_Surface * bouton_surface = NULL;
    /**
     * \brief Création de la texture normale
     */
    bouton_surface = TTF_RenderText_Blended(fenetre->police, texte, couleur);
    bouton->normale = SDL_CreateTextureFromSurface(fenetre->renderer, bouton_surface);
    SDL_FreeSurface(bouton_surface);

    /**
     * \brief Création de la texture survol
     */
    bouton_surface = TTF_RenderText_Shaded_Wrapped (fenetre->police, texte,couleur, wrap, 1000);
    bouton->survol = SDL_CreateTextureFromSurface(fenetre->renderer, bouton_surface);
    SDL_FreeSurface(bouton_surface);

    /**
     * \brief attribution des coordonnées au bouton
     */
    bouton->dst.x = x;
    bouton->dst.y = y;
    SDL_QueryTexture(bouton->survol, NULL, NULL, &bouton->dst.w, &bouton->dst.h);
    return bouton;
}

void supression_bouton(bouton_t ** bouton){
    /**
     * \brief Supression de la texture normale
     */
    SDL_DestroyTexture((*bouton)->normale);
    /**
     * \brief Supression de la texture survol
     */
    SDL_DestroyTexture((*bouton)->survol);
    /**
     * \brief destruction du bouton et libération de la mémoire
     * 
     */
    free(*bouton);
    *bouton = NULL;
}

void position_bouton(bouton_t * bouton, const int x, const int y){
    /**
     * \brief attribution des coordonnées au bouton
     */
    bouton->dst.x = x;
    bouton->dst.y = y;
}