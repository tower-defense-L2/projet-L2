/**
 * \file placement_tours.c
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \brief source fonction placement et suppression des tours
 * \version 0.1
 * \date 2023-03-22
 * 
 * 
 */

#include "../include/placement_tours.h"
#include "../include/possibilite_tour.h"



//met une tour sur la sase sélecionnée
void placement_tour(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour)
{

    if(position_possible){
        emplacement->tour = 1;
        joueur->argent = joueur->argent - tour->cout;
    }

}

// supprime la tour de la sase sélecionnée
void suppression_tour(emplacement_T *emplacement, tour_T *tour)
{
    if(suppression_possible)
    {
        emplacement->tour = NULL;
    }

}