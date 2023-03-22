/**
 * \file interaction_souris.c
 * \author meo (meo.prn@outlook.fr)
 * \brief source des fonctions de gestion de la souris 
 * \version 0.1.0
 * \date 2023-03-22
 * 
 * 
 */
#include "../../include/interaction_souris.h"


int souris_dessu(const int x, const  int y, const SDL_Rect *rect){
    /**
     * \brief comparaison de la coordonnée de la souris avec les coordonnées du rectangle
     */
    if(x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h){
        return 1;
    }
    return 0;
}

int gestion_bouton(const bouton_t * bouton, pack_t * fenetre , const int x, const int y){
    /**
     * \brief si la souris est sur le bouton, on affiche le bouton survol
     */
    if(souris_dessu(x, y, &bouton->dst)){
        SDL_RenderCopy(fenetre->renderer, bouton->survol, NULL, &bouton->dst);
        return 1;
    }
    /**
     * \brief sinon on affiche le bouton normale
     */
    SDL_RenderCopy(fenetre->renderer, bouton->normale, NULL, &bouton->dst);
    return 0;
}