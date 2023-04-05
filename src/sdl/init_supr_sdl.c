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

extern
pack_t * creation_pack(char * titre, int width, int height, int flags, int taille_police){
    pack_t * fenetre = malloc(sizeof(pack_t));

    // Création de la fenêtre
    fenetre->fenetre = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    // Gestion d'erreur de la fenêtre
    if(fenetre->fenetre == NULL){ 
        printf("Erreur de création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    // création du renedrer
    fenetre->renderer = SDL_CreateRenderer(fenetre->fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    // gestion d'erreur du renderer
    if(fenetre->renderer == NULL){
        printf("Erreur de création du renderer : %s", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    // creation de la police
    fenetre->police = TTF_OpenFont("./ressources/arial.ttf", taille_police);
    // gestion d'erreur de la police
    if(fenetre->police == NULL){
        printf("Erreur de création de la police : %s", TTF_GetError());
        SDL_Quit();
        return NULL;
    }

    return fenetre;
}

extern
int initilalisation_sdl(){
    // Initialisation de la SDL avecc gestion d'erreur
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }
    // Initialisation de SDL_ttf avec gestion d'erreur
    if(TTF_Init() < 0){
        printf("Erreur d'initialisation de SDL_ttf : %s", TTF_GetError());
        SDL_Quit();
        return 1 ;
    }
    return 0;
}


extern
void supression_pack(pack_t ** fenetre){
    // Supression de la police
    TTF_CloseFont((*fenetre)->police);
    // Supression du renderer
    SDL_DestroyRenderer((*fenetre)->renderer);
    // Supression de la fenêtre
    SDL_DestroyWindow((*fenetre)->fenetre);
    free(*fenetre);
    *fenetre = NULL;
}

extern
void supression_sdl(){
    // Quitte SDL_ttf
    TTF_Quit();
    // Quitte la SDL
    SDL_Quit();
}


extern
int load_bitmap(const char *path, SDL_Texture ** texture, pack_t * fenettre){
    char * path2 = malloc(sizeof(char) * 100);
    strcpy(path2, RESSOURCES);
    strcat(path2, path);
    strcat(path2, ".bmp");
    SDL_Surface * fond = NULL;
    // load de la bitmap
    fond = SDL_LoadBMP(path2);
    // gestion d'erreur du load
    if(fond == NULL){
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }


    // création de la texture
    *texture = SDL_CreateTextureFromSurface(fenettre->renderer, fond);
    // gestion d'erreur de la texture
    if(*texture == NULL){
        printf("Erreur de création de la texture : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    // libération de la surface
    free(path2);
    SDL_FreeSurface(fond);
    return 0;
}

extern
void supression_texture(texture_t * texture){
    // Supression de la texture
    SDL_DestroyTexture(texture->texture);
    // reatribution des pointeurs de la liste
    if(texture->precedent != NULL){
        texture->precedent->suivant = texture->suivant;
    }
    if(texture->suivant != NULL){
        texture->suivant->precedent = texture->precedent;
    }
    // destruction de la texture et libération de la mémoire
    free(texture);
    texture = NULL;
}

extern
void supression_texture_liste(texture_t * texture){
    // Supression de la liste de texture en récursivité
    if(texture->suivant != NULL){
        supression_texture_liste(texture->suivant);
    }
    // supression de la texture actuelle
    supression_texture(texture);
}

extern SDL_Texture * creation_texte(pack_t * fenetre, char * texte, SDL_Color couleur){
    SDL_Surface * text_surface = NULL;
    SDL_Texture * text_texture = NULL;
    // Création de la surface
    text_surface = TTF_RenderText_Blended(fenetre->police, texte, couleur);
    // gestion d'erreur de la surface
    if(text_surface == NULL){
        printf("Erreur de création de la surface : %s", TTF_GetError());
        SDL_Quit();
        return NULL;
    }
    text_texture = SDL_CreateTextureFromSurface(fenetre->renderer, text_surface);
    // gestion d'erreur de la texture
    if(text_texture == NULL){
        printf("Erreur de création de la texture : %s", SDL_GetError());
        SDL_Quit();
        return NULL;
    }
    // libération de la surface
    SDL_FreeSurface(text_surface);
    return text_texture;
}


extern
bitexture_t * creation_bouton(pack_t * fenetre, char * texte,
                SDL_Color couleur, SDL_Color wrap, int x, int y){
    
    bitexture_t * bouton = malloc(sizeof(bitexture_t));
    SDL_Surface * bouton_surface = NULL;
    // Création de la texture normale
    bouton->normale = creation_texte(fenetre, texte, couleur);
    // gestion d'erreur de la texture
    if(bouton->normale == NULL){
        return NULL;
    }

    // Création de la texture survol
    bouton_surface = TTF_RenderText_Shaded_Wrapped (fenetre->police, texte,couleur, wrap, 1000);
    // gestion d'erreur de la surface
    if(bouton_surface == NULL){
        printf("Erreur de création de la surface : %s", TTF_GetError());
        SDL_Quit();
        return NULL;
    }
    bouton->survol = SDL_CreateTextureFromSurface(fenetre->renderer, bouton_surface);
    // gestion d'erreur de la texture
    if(bouton->survol == NULL){
        printf("Erreur de création de la texture : %s", SDL_GetError());
        SDL_Quit();
        return NULL;
    }
    SDL_FreeSurface(bouton_surface);

    // brief attribution des coordonnées au bouton
    bouton->dst.x = x;
    bouton->dst.y = y;
    SDL_QueryTexture(bouton->survol, NULL, NULL, &bouton->dst.w, &bouton->dst.h);
    return bouton;
}

extern
void supression_bouton(bitexture_t ** bouton){
    // Supression de la texture normale
    SDL_DestroyTexture((*bouton)->normale);
    // Supression de la texture survol
    SDL_DestroyTexture((*bouton)->survol);
    // destruction du bouton et libération de la mémoire
    free(*bouton);
    *bouton = NULL;
}

extern
void position_bitexture(bitexture_t * bouton, const int x, const int y){
    // attribution des coordonnées au bouton
    bouton->dst.x = x;
    bouton->dst.y = y;
}

extern
bitexture_t * creation_bitexture(pack_t * fenetre, char * path1, char * path2, int x, int y){
    bitexture_t * bitexture = malloc(sizeof(bitexture_t));
    // Chargement de la texture normale
    load_bitmap(path1, &bitexture->normale, fenetre);
    // Chargement de la texture survol
    load_bitmap(path2, &bitexture->survol, fenetre);
    // attribution des coordonnées au bouton
    bitexture->dst.x = x;
    bitexture->dst.y = y;
    SDL_QueryTexture(bitexture->survol, NULL, NULL, &bitexture->dst.w, &bitexture->dst.h);
    // gestion d'erreur de la texture
    if (bitexture->normale == NULL || bitexture->survol == NULL){
        SDL_Quit();
        return NULL;
    }
    return bitexture;
}