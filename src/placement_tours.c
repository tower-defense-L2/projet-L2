#include "../include/placement_tours.h"

typedef struct liste_tour_S {
    tour_T *tour;
    struct liste_tour_S *suivant;
} liste_tour_T;

liste_tour_T *liste_tour = NULL;

extern
int placement_possible(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour)
{   
    if(emplacement == NULL || joueur == NULL || tour == NULL){
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

//met une tour sur la sase sélecionnée
extern
void placement_tour(emplacement_T *emplacement, joueur_T *joueur, tour_T *tour)
{
    if (placement_possible(emplacement, joueur, tour)){
        tour->position = emplacement->position;
        emplacement->tour = tour;
        joueur->argent -= tour->cout;
    }
}

// supprime la tour de la sase sélecionnée
extern
void suppression_tour(emplacement_T *emplacement, tour_T *tour)
{
    if (emplacement->tour != NULL)
    {
        free(emplacement->tour);
        emplacement->tour = NULL;
    }

}

extern
tour_T * cree_tour()
{  
    liste_tour_T *tmp = malloc(sizeof(liste_tour_T));
    tmp->suivant = NULL;
    tmp->tour= NULL;
    tour_T *tour = malloc(sizeof(tour_T));
    if(liste_tour==NULL){
        liste_tour = tmp;
        tour->id = 1;
    } 
    while(tmp->suivant != NULL){
        tour->id = tmp->tour->id + 1;
        tmp = tmp->suivant;
    }
    tour->degat = DEGAT_TOUR_BASE;
    tour->portee = PORTEE_TOUR_BASE;
    tour->cout = COUT_TOUR_BASE;
    tour->frequence = FREQUENCE_TOUR_BASE;
    tour->position.x = 1;
    tour->position.y = 1;
    return tour;
}

extern
detruire_tour(tour_T *tour)
{
    free(tour);
    tour = NULL;
}

extern
detruire_tours()
{
    liste_tour_T *tmp = liste_tour;
    while(tmp != NULL){
        detruire_tour(tmp->tour);
        tmp = tmp->suivant;
    }
    free(liste_tour);
}