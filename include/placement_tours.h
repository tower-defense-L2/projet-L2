/**
 * \file placement_tours.h
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \brief Afin de mettre une tour sur la carte ou d'en supprimer une
 * \version 0.1
 * \date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "stdlib.h"
#include "const.h"
#include "struct.h"

/**
 * \brief Pose une tour sur la case et débite la solde du joueur de son coût
 * \param emplacement // La case visée pour le placement de la tours sur la carte
 * \param joueur // Pour soustraire le coût d'une tour à l'argent du joueur
 * \param tour // Est null si il n'y a pas de tour
 */
void placement_tour(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour);



/**
 * \brief Supprime la tour de la case
 * 
 * \param emplacement // La case visée pour le placement de la tours sur la carte
 * \param tour Est null si il n'y a pas de tour
 */
void suppression_tour(emplacement_T *emplacement, tour_T *tour);