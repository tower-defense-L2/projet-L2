/**
 * \file mouvement_ennemi.c
 * \author meo (meo.prn@outlook.fr)
 * \brief fonction permettant de gére le comportement des ennemis
 * \version 0.1.0
 * \date 2023-04-07
 * 
 */
#include "../include/mouvement_ennemi.h"

/**
 * \brief primitive de la structure liste_ennemi_T
 */
typedef struct liste_ennemi_S {
    ennemi_T *enemi;
    struct liste_ennemi_S *suivant;
    struct liste_ennemi_S *precedent;
} liste_ennemi_T;
/**
 * \struct liste_ennemi_T
 * \brief structure contenant les pointeurs sur l'ennemi et les pointeurs sur les ennemis suivantes et précédentes
 * \param enemi pointeur sur l'ennemi
 * \param suivant pointeur sur la liste_ennemi_T suivante
 * \param precedent pointeur sur la liste_ennemi_T précédente
 */

liste_ennemi_T *liste_enemi = NULL;

case_T * hors_jeux;

/**
 * \brief inflige des degats a un joueur et detruit l'ennemi
 * 
 * \param enemi pointeur vers l'ennemi
 * \param joueur pointeur vers le joueur
 */
static
void dega_ennemi(ennemi_T *enemi, joueur_T *joueur){
    joueur->vie -= enemi->degat;
    detruire_ennemi(enemi->id);
}

/**
 * \brief fait avancer toutes les billes et vérifie si elles sont arrivées au bout du chemin
 * 
 * \param bille pointeur vers la bille
 * \param joueur pointeur vers le joueur
 * \return int -1 si erreur / 0 si la bille n'a pas bougé / 1 si la bille a bougé
 */
static
int mouvement_bille(ennemi_T* bille, joueur_T *joueur)
{   
    // vérifie que les pointeurs ne sont pas NULL
    if(bille == NULL || joueur == NULL){
        return -1;
    }
    // initialise la case de départ
    case_T *chemin = NULL;

    //vérifie si la bille est sortie
    if(bille->position.x == -1 && bille->position.y == -1){
        //initialise a la case de départ
        chemin = hors_jeux;
    }
    else{
        //initialise a la case de la bille
        chemin = get_case(bille->position.x, bille->position.y);
    }
    //vérifie que la case existe
    if(chemin == NULL){
        return -1;
    }
    //vérifie que la case suivante existe sinon l'ennemi est arrivé
    if (chemin->case_pl.chemin.suivant == NULL){
        dega_ennemi(bille, joueur);
        chemin->case_pl.chemin.enemi = NULL;
        return 1;
    }
    //vérifie que la case suivante est libre
    if (chemin->case_pl.chemin.suivant->enemi == NULL){
        bille->position = chemin->case_pl.chemin.suivant->position; // met la position de la bille sur la case suivante
        chemin->case_pl.chemin.suivant->enemi = bille; // met la bille sur la case suivante
        chemin->case_pl.chemin.enemi = NULL;
        return 1;
    }
    return -1;
}

extern
void detruire_ennemi(int id)
{
    liste_ennemi_T *tmp = liste_enemi;
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
            if (liste_enemi->enemi == NULL)
                free(liste_enemi);
            return;
        }
        tmp = tmp->suivant;
    }
    if (liste_enemi->enemi == NULL)
        free(liste_enemi);
}

extern
void detruire_ennemis()
{
    liste_ennemi_T *tmp = liste_enemi;
    while (tmp != NULL)
    {
        liste_ennemi_T *tmp2 = tmp->suivant;
        free(tmp->enemi);
        free(tmp);
        tmp = tmp2;
    }
    liste_enemi = NULL;
}

/**
 * \brief crée une bille avec les paramètres donnés en position -1 -1 et l'ajoute à la liste des billes
 * 
 * \param vie vie de la bille
 * \param reconpense argent gagné en tuant la bille
 * \param vitesse fréquence de déplacement de la bille en s/60
 * \param degat dégat de la bille
 */
static
void creer_ennemi(int vie, int reconpense, int vitesse, int degat)
{
    ennemi_T *enemi = malloc(sizeof(ennemi_T));
    enemi->id = 1;
    enemi->vie = vie;
    enemi->reconpense = reconpense;
    enemi->vitesse = vitesse;
    enemi->degat = degat;
    enemi->position = (position_T){-1, -1};

    liste_ennemi_T *tmp = malloc(sizeof(liste_ennemi_T));
    tmp->enemi = enemi;
    tmp->suivant = NULL;
    tmp->precedent = liste_enemi;
    if (liste_enemi != NULL)
    {
        liste_enemi->suivant = tmp;
        tmp->enemi->id = liste_enemi->enemi->id + 1;
    }
    liste_enemi = tmp;
}

extern
void creer_vague(int num_vague)
{
    if(hors_jeux == NULL){
        hors_jeux = malloc(sizeof(case_T));
        hors_jeux->type = CHEMIN;
        hors_jeux->case_pl.chemin.position = (position_T){-1, -1};
        hors_jeux->case_pl.chemin.enemi = NULL;
        hors_jeux->case_pl.chemin.suivant = get_case(X_START, Y_START)->case_pl.chemin.suivant;
    }
    for(int i = 0; i < 3*num_vague; i++)
    {
        creer_ennemi(VIE_ENNEMI_BASE, RECOMPENSE_ENNEMI_BASE, VITESSE_ENNEMI_BASE, DEGAT_ENNEMI_BASE);
    }
}

extern
int vague_terminee(){
    if (liste_enemi == NULL)
    {
        return 1;
    }
    return 0;
}

/**
 * \brief renvoie l'ennemi avec l'id le plus petit de la liste des ennemis (le plus en avant sur le chemin)
 * 
 * \return liste_enemi_T* pointeur vers l'ennemi avec l'id le plus petit
 */
static
liste_ennemi_T *get_mini_id()
{
    liste_ennemi_T *tmp = liste_enemi;
    liste_ennemi_T *mini = tmp;
    while (tmp != NULL)
    {
        if (tmp->enemi->id < mini->enemi->id)
        {
            mini = tmp;
        }
        tmp = tmp->suivant;
    }
    return mini;
}


extern
void ennemi_avancer(joueur_T *joueur, unsigned int diviseur)
{
    liste_ennemi_T *tmp = get_mini_id();
    while (tmp != NULL)
    {
        if(tmp->enemi->vitesse % diviseur == 0){
            mouvement_bille(tmp->enemi,joueur);
        }
        tmp = tmp->precedent;
    }
}