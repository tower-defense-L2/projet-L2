#include "../include/placement_tours.h"
#include "../include/possibilite_tours.h"



//met une tour sur la sase sélecionnée
extern
void placement_tour(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour)
{

    if(position_possible){
        emplacement->tour = 1;
        joueur->argent = joueur->argent - tour->cout;
    }

}

// supprime la tour de la sase sélecionnée
extern
void suppression_tour(emplacement_T *emplacement, tour_T *tour)
{
    if(suppression_possible)
    {
        emplacement->tour = NULL;
    }

}