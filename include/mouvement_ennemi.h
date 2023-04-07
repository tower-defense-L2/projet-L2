/**
 * \file mouvement_ennemi.h
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \author meo (meo.prn@outlook.fr)
 * \brief vérifie la possiblité de déplacement d'une bille
 * \version 0.1
 * \date 2023-03-22
 * 
 * 
 */

#ifndef MOUVEMENT_ENNEMI_H
#define MOUVEMENT_ENNEMI_H
#include <stdlib.h>
#include "const.h"
#include "struct.h"
#include "map.h"


/**
 * \brief détruit une bille dont l'id est donné en paramètre
 * 
 * \param id id de la bille à détruire
 */
extern
void detruire_enemi(int id);

/**
 * \brief détruit toutes les billes
 * 
 */
extern
void detruire_enemis();


/**
 * \brief crée une vague d'ennemis en augmentant la difficulté avec le numéro de la vague
 * 
 * \param num_vague numéro de la vague
 */
extern
void creer_vague(int num_vague);

/**
 * \brief vérifie si toutes les billes sont détruites
 * 
 * \return int 1 si toutes les billes sont détruites / 0 sinon
 */
extern
int vague_terminee();

/**
 * \brief déplace toutes les billes et vérifie si elles sont arrivées au bout du chemin
 * 
 * \param joueur pointeur sur le joueur
 */
extern
void enemi_avancer(joueur_T *joueur);
#endif