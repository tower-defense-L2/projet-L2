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
    tour_T *tour = malloc(sizeof(tour_T));
    tour->degat = DEGAT_TOUR_BASE;
    tour->portee = PORTEE_TOUR_BASE;
    tour->cout = COUT_TOUR_BASE;
    tour->frequence = FREQUENCE_TOUR_BASE;
    tour->position.x = 1;
    tour->position.y = 1;
    if (liste_tour == NULL)
    {
        liste_tour = malloc(sizeof(liste_tour_T));
        liste_tour->tour = tour;
        tour->id = 0;
        liste_tour->suivant = NULL;
    }
    else
    {
        liste_tour_T *tmp = liste_tour;
        while (tmp->suivant != NULL)
        {
            tmp = tmp->suivant;
        }
        tmp->suivant = malloc(sizeof(liste_tour_T));
        tmp->suivant->tour = tour;
        tour->id = tmp->tour->id + 1;
        tmp->suivant->suivant = NULL;
    }
    return tour;
}

extern
void detruire_tour(tour_T *tour)
{
    free(tour);
    tour = NULL;
}

extern
void detruire_tours()
{
    liste_tour_T *tmp = liste_tour;
    while(tmp != NULL){
        detruire_tour(tmp->tour);
        tmp = tmp->suivant;
    }
    free(liste_tour);
}

/**
 * \brief inflige des dégats à un ennemi et le tue si il n'a plus de vie
 * 
 * \param joueur pointeur sur le joueur
 * \param tour pointeur sur la tour
 * \param ennemi pointeur sur l'ennemi
 */
static
void dega_tour(joueur_T * joueur, tour_T *tour, ennemi_T *ennemi){
    ennemi->vie -= tour->degat;
    if(ennemi->vie <= 0){
        joueur->argent += ennemi->reconpense;
        detruire_ennemi(ennemi->id);
    }
}

/**
 * \brief vérifie si un ennemi est dans la portée de la tour et l'attaque si c'est le cas
 * 
 * \param tour pointeur sur la tour
 * \param map pointeur sur la map
 * \return int 1 si l'ennemi est dans la portée / 0 sinon
 */
static
int tour_portee(tour_T *tour, map_T *map, joueur_T * joueur){
    for(int i = 1; i<=tour->portee; i++){
        if(dans_map((position_T){tour->position.x+i, tour->position.y}) &&
            map->cases[tour->position.x+i][tour->position.y]->type == CHEMIN &&
            map->cases[tour->position.x+i][tour->position.y]->case_pl.chemin.enemi!=NULL){
                dega_tour(joueur, tour, map->cases[tour->position.x+i][tour->position.y]->case_pl.chemin.enemi);
                return 1;
        }
        if(dans_map((position_T){tour->position.x+i, tour->position.y+i}) &&
            map->cases[tour->position.x+i][tour->position.y+i]->type == CHEMIN &&
            map->cases[tour->position.x+i][tour->position.y+i]->case_pl.chemin.enemi!=NULL){
                dega_tour(joueur, tour, map->cases[tour->position.x+i][tour->position.y+i]->case_pl.chemin.enemi);
                return 1;
        }
        if(dans_map((position_T){tour->position.x, tour->position.y+i}) &&
            map->cases[tour->position.x][tour->position.y+i]->type == CHEMIN &&
            map->cases[tour->position.x][tour->position.y+i]->case_pl.chemin.enemi!=NULL){
                dega_tour(joueur, tour, map->cases[tour->position.x][tour->position.y+i]->case_pl.chemin.enemi);
                return 1;
        }
        if(dans_map((position_T){tour->position.x-i, tour->position.y+i}) &&
            map->cases[tour->position.x-i][tour->position.y+i]->type == CHEMIN &&
            map->cases[tour->position.x-i][tour->position.y+i]->case_pl.chemin.enemi!=NULL){
                dega_tour(joueur, tour, map->cases[tour->position.x-i][tour->position.y+i]->case_pl.chemin.enemi);
                return 1;
        }
        if(dans_map((position_T){tour->position.x-i, tour->position.y}) &&
            map->cases[tour->position.x-i][tour->position.y]->type == CHEMIN &&
            map->cases[tour->position.x-i][tour->position.y]->case_pl.chemin.enemi!=NULL){
                dega_tour(joueur, tour, map->cases[tour->position.x-i][tour->position.y]->case_pl.chemin.enemi);
                return 1;
        }
        if(dans_map((position_T){tour->position.x-i, tour->position.y-i}) &&
            map->cases[tour->position.x-i][tour->position.y-i]->type == CHEMIN &&
            map->cases[tour->position.x-i][tour->position.y-i]->case_pl.chemin.enemi!=NULL){
                dega_tour(joueur, tour, map->cases[tour->position.x-i][tour->position.y-i]->case_pl.chemin.enemi);
                return 1;
        }
        if(dans_map((position_T){tour->position.x, tour->position.y-i}) &&
            map->cases[tour->position.x][tour->position.y-i]->type == CHEMIN &&
            map->cases[tour->position.x][tour->position.y-i]->case_pl.chemin.enemi!=NULL){
                dega_tour(joueur, tour, map->cases[tour->position.x][tour->position.y-i]->case_pl.chemin.enemi);
                return 1;
        }
        if(dans_map((position_T){tour->position.x+i, tour->position.y-i}) &&
            map->cases[tour->position.x+i][tour->position.y-i]->type == CHEMIN &&
            map->cases[tour->position.x+i][tour->position.y-i]->case_pl.chemin.enemi!=NULL){
                dega_tour(joueur, tour, map->cases[tour->position.x+i][tour->position.y-i]->case_pl.chemin.enemi);
                return 1;
        }
    }
    return 0;
}

extern
void tour_action(joueur_T * joueur, map_T *map, unsigned int diviseur)
{
    liste_tour_T *tmp = liste_tour;
    while(tmp != NULL){
        if(tmp->tour->frequence % diviseur == 0){
            tour_portee(tmp->tour, map, joueur);
        }
        tmp = tmp->suivant;
    }
}