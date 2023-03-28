/**
 * \file possibilite_tours.c
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \brief source fonction gestion placement et suppression tours
 * \version 0.1
 * \date 2023-03-22
 * 
 * 
 */
#include "../include/possibilite_tours.h"


int position_possible(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour, type_case_T *type)
{

    //vérifie si la case est pour une tour
    if ( type != emplacement)
    {
        return 0;
    }

    //vérifie si il ya une tour sur la case
    if (emplacement->tour != NULL)
    {
        return 0;
    }
    
    //vérifie si le joueur a le solde nécessaire pour acheter la tour
    if ( joueur->argent < tour->cout)
    {
        return 0;
    }

    return 1;

}



int suppression_possible(emplacement_T *emplacement, chemin_T *chemin, type_case_T* vide)
{

    //vérifie qu'il y a une tour sur la case
    if (emplacement->tour != NULL )
    {
        return 1;
    }
}