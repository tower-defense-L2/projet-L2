/**
 * \file mouvement_ennemi.c
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \brief vérifie si une bille peut se rendre dans la salle suivante, cans ce cas
 *         le fait et suprime l'ennemi qui a bougé de ses anciennes coordonnées
 * \version 0.1
 * \date 2023-03-22
 * 
 * 
 */

#include "../include/mouvement_ennemi.h"

extern
int mouvement_bille(chemin_T *chemin)
{

    //vérifie que la case suivante est libre
    if (chemin->suivant->enemi == NULL)
    {
        chemin->enemi->position = chemin->suivant->position; // met la bille sur la case suivante
        chemin->suivant->enemi = NULL;
        chemin->enemi = NULL;
        return 1;
    }

    return 0;
}

