/**
 * \file dega.c
 * \author meo (meo.prn@outlook.fr)
 * \brief gestion des degats des tours et des ennemis
 * \version 0.1.0
 * \date 2023-04-03
 * 
 */

#include "../include/dega.h"

static
void dega_tour(joueur_T * joueur,tour_T *tour, ennemi_T *ennemi){
    ennemi->vie -= tour->degat;
    if(ennemi->vie <= 0){
        joueur->argent += ennemi->reconpense;
        detruire_enemi(ennemi->id);
    }
}

static
void dega_enemi(ennemi_T *enemi, joueur_T *joueur){
    joueur->vie -= enemi->degat;
}