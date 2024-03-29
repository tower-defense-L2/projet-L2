#include "../../include/interaction_souris.h"

extern
int souris_dessu(const int x, const  int y, const SDL_Rect *rect){
    // comparaison de la coordonnée de la souris avec les coordonnées du rectangle
    if(x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h){
        return 1;
    }
    return 0;
}

extern
int gestion_bitexture(const bitexture_t * bouton, pack_t * fenetre , const int x, const int y){
    // si la souris est sur le bouton, on affiche le bouton survol
    if(souris_dessu(x, y, &bouton->dst)){
        SDL_RenderCopy(fenetre->renderer, bouton->survol, NULL, &bouton->dst);
        return 1;
    }
    // sinon on affiche le bouton normale
    SDL_RenderCopy(fenetre->renderer, bouton->normale, NULL, &bouton->dst);
    return 0;
}