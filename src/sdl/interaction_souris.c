#include "../../include/interaction_souris.h"


int souris_dessu(const int x, const  int y, const SDL_Rect *rect){

    if(x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h){
        return 1;
    }
    return 0;
}

int gestion_bouton(const bouton_t * bouton, pack_t * fenetre , const int x, const int y){
    if(souris_dessu(x, y, &bouton->dst)){
        SDL_RenderCopy(fenetre->renderer, bouton->survol, NULL, &bouton->dst);
        return 1;
    }
    SDL_RenderCopy(fenetre->renderer, bouton->normale, NULL, &bouton->dst);
    return 0;
}