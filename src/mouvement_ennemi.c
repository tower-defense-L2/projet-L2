#include "../include/mouvement_ennemi.h"

typedef struct liste_enemi_S {
    ennemi_T *enemi;
    struct liste_enemi_S *suivant;
    struct liste_enemi_S *precedent;
} liste_enemi_T;

liste_enemi_T *liste_enemi = NULL;


extern
int mouvement_bille(chemin_T *chemin)
{
    //vérifie que la case suivante existe
    if (chemin->suivant == NULL)
    {
        return 0;
    }
    //vérifie que l'ennemi existe
    if (chemin->enemi == NULL)
    {
        return 0;
    }
    //vérifie que la case suivante est libre
    if (chemin->suivant->enemi == NULL)
    {
        chemin->enemi->position = chemin->suivant->position; // met la position de la bille sur la case suivante
        chemin->suivant->enemi = chemin->enemi; // met la bille sur la case suivante
        chemin->enemi = NULL;
        return 1;
    }

    return 0;
}

extern
void detruire_enemi(int id)
{
    liste_enemi_T *tmp = liste_enemi;
    while (tmp != NULL)
    {
        if (tmp->enemi->id == id)
        {
            if (tmp->suivant != NULL)
            {
                tmp->suivant->precedent = tmp->precedent;
            }
            if (tmp->precedent != NULL)
            {
                tmp->precedent->suivant = tmp->suivant;
            }
            free(tmp->enemi);
            free(tmp);
            return;
        }
        tmp = tmp->suivant;
    }
}

extern
void detruire_enemis()
{
    liste_enemi_T *tmp = liste_enemi;
    while (tmp != NULL)
    {
        liste_enemi_T *tmp2 = tmp->suivant;
        free(tmp->enemi);
        free(tmp);
        tmp = tmp2;
    }
}

extern
void creer_enemi(int vie, int reconpense, int vitesse, int degat)
{
    ennemi_T *enemi = malloc(sizeof(ennemi_T));
    enemi->id = 1;
    enemi->vie = vie;
    enemi->reconpense = reconpense;
    enemi->vitesse = vitesse;
    enemi->degat = degat;
    enemi->position = (position_T){-1, -1};

    liste_enemi_T *tmp = malloc(sizeof(liste_enemi_T));
    tmp->enemi = enemi;
    tmp->suivant = liste_enemi;
    tmp->precedent = NULL;
    if (liste_enemi != NULL)
    {
        liste_enemi->precedent = tmp;
        tmp->enemi->id = liste_enemi->enemi->id + 1;
    }
    liste_enemi = tmp;
}

extern
void creer_vague(int num_vague)
{
    for(int i = 0; i < 3*num_vague; i++)
    {
        creer_enemi(VIE_ENNEMI_BASE, RECOMPENSE_ENNEMI_BASE, VITESSE_ENNEMI_BASE, DEGAT_ENNEMI_BASE);
    }
}

extern
int vague_termine(){
    if (liste_enemi == NULL)
    {
        return 1;
    }
    return 0;
}