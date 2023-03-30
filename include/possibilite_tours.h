/**
 * \file possibilite_tours.h
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \brief  Vérification des actions liées aux tours
 * \version 0.1
 * \date 2023-03-22
 * 
 * 
 */

#include "stdlib.h"
#include "const.h"
#include "struct.h"

/**
 * \brief verifie si le placement d'une tour est possible
 * 
 * \param emplacement // La case visée pour le placement de la tours sur la carte
 * \param joueur // Pour soustraire le coût d'une tour à l'argent du joueur
 * \param tour // Est null si il n'y a pas de tour
 * \param type // Donne le type de la case, si la case est destinée à une tour (emplacement) ou une bille (chemin)
 * 
 * \return int 0 si impossible / 1 si possible
 */
extern
int position_possible(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour, type_case_T *type);



/**
 * \brief vérifie si la suppression d'une tour est possible
 * 
 * \param emplacement // La case visée pour le placement de la tours sur la carte
 * \param chemin // Le type de case ou les ennemis peuvent se déplacer
 * \param vide // correspond au décor
 * \return int int 0 si impossible / 1 si possible
 */
extern
int suppression_possible(emplacement_T *emplacement, chemin_T *chemin, type_case_T* vide);