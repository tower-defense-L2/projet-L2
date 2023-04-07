/**
 * \file placement_tours.h
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \author meo (meo.prn@outlook.fr)
 * \brief Afin de mettre une tour sur la carte ou d'en supprimer une
 * \version 0.1
 * \date 2023-03-22
 * 
 * 
 */
#ifndef PLACEMENT_TOURS_H
#define PLACEMENT_TOURS_H
#include <stdlib.h>
#include "const.h"
#include "struct.h"

/**
 * \brief Vérifie si le placement de la tour est possible
 * 
 * \param emplacement position a vérifier
 * \param joueur pointeur sur le joueur
 * \param tour tour a placer
 * \return int 1 si le placement est possible, 0 sinon
 */
extern
int placement_possible(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour);

/**
 * \brief Pose une tour sur la case et débite la solde du joueur de son coût
 * \param emplacement // La case visée pour le placement de la tours sur la carte
 * \param joueur // Pour soustraire le coût d'une tour à l'argent du joueur
 * \param tour // Est null si il n'y a pas de tour
 */
extern
void placement_tour(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour);


/**
 * \brief Supprime la tour de la case
 * 
 * \param emplacement // La case visée pour le placement de la tours sur la carte
 * \param tour Est null si il n'y a pas de tour
 */
extern
void suppression_tour(emplacement_T *emplacement, tour_T *tour);

/**
 * \brief Crée une tour avec les caractéristiques de base
 * 
 * \return tour_T* pointeur sur la tour créée
 */
extern 
tour_T * cree_tour();

/**
 * \brief detruit une tour donnée en paramètre
 * 
 * \param tour pointeur sur la tour à détruire
 */
extern
detruire_tour(tour_T *tour);

/**
 * \brief detruit toutes les tours de la carte
 * 
 */
extern
detruire_tours();
#endif