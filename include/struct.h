/**
 * \file struct.h
 * \author meo (meo.prn@outlook.fr)
 * \author Antoine Sainty (Antoine.Sainty.Etu@univ-lemans.fr)
 * \brief definition des differente structure utilisé dans le programme
 * \version 0.1.0
 * \date 2023-01-23
 * 
 * 
 */

#ifndef STRUCT_H
#define STRUCT_H
#include "const.h"

/**
 * \struct position_S
 * \brief structure contenant les coordonnées d'un élément
 */
typedef struct position_S {
    int x; /*!< coordonnée x */
    int y; /*!< coordonnée y */
} position_T;

/**
 * \struct tour_S
 * \brief structure contenant les informations d'une tour
 */
typedef struct tour_S {
    int id; /*!< identifiant de la tour */
    int degat; /*!< degat de la tour */
    int portee; /*!< portée de la tour */
    int cout; /*!< cout de la tour */
    int frequence; /*!< frequence de tir de la tour en s/60 */
    position_T position; /*!< position de la tour */
} tour_T;

/**
 * \struct ennemi_S
 * \brief structure contenant les informations d'un ennemi
 */
typedef struct ennemi_S {
    int id; /*!< identifiant de l'ennemi */
    int vie; /*!< vie de l'ennemi */
    int vitesse; /*!< vitesse de l'ennemi */
    int degat; /*!< degat de l'ennemi */
    position_T position; /*!< position de l'ennemi */
} ennemi_T;

/**
 * \struct joueur_S
 * \brief structure contenant les informations d'un joueur
 */
typedef struct joueur_S {
    int argent; /*!< argent du joueur */
    int vie; /*!< vie du joueur */
} joueur_T;

/**
 * \struct emplacement_S
 * \brief structure contenant les informations d'un emplacement
 */
typedef struct emplacement_S {
    position_T position; /*!< position de l'emplacement */
    tour_T* tour; /*!< pointeur sur la tour, NULL si rien n'est placé */
} emplacement_T;

/**
 * \struct chemin_S
 * \brief structure contenant les informations d'un chemin
 */
typedef struct chemin_S {
    position_T position; /*!< position du chemin */
    ennemi_T* enemi; /*!< pointeur sur l'ennemi, NULL si aucun ennemi est présent */
    struct chemin_S* suivant; /*!< pointeur sur le chemin suivant, NULL si la fin du parcours */
} chemin_T;

typedef enum type_case_E {
    EMPLACEMENT, /*!< emplacement de tours possible */
    OBSTACLE, /*!< emplacement d'obstacle */
    CHEMIN, /*!< chemin que les ennemis peuvent emprunté */
    VIDE /*!< du décor */
} type_case_T;

/**
 * \union case_U
 * \brief union contenant les informations d'une case
 */
typedef union case_U {
    emplacement_T emplacement; /*!< emplacement de la case */
    chemin_T chemin; /*!< chemin de la case */
} case_TU;


typedef struct case_S {
    type_case_T type; /*!< type de la case */
    case_TU case_pl; /*!< case */
} case_T;

/**

 * \struct map_S
 * \brief structure contenant les informations d'une carte
 */
typedef struct map_S {
    case_T* cases[HAUTEUR][LARGEUR]; /*!< tableau de pointeur sur case_T */
} map_T;

#endif