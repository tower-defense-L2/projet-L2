/**
 * \file struct.h
 * \author meo (meo.prn@outlook.fr)
 * \brief definition des differente structure utilisé dans le programme
 * \version 0.1.0
 * \date 2023-01-23
 * 
 * 
 */

#ifndef STRUCT_H
#define STRUCT_H

typedef struct position_S position_T;
typedef struct tour_S tour_T;
typedef struct enemi_S enemi_T;
typedef struct joueur_S joueur_T;


typedef struct bordure_S bordure_T;
typedef struct chemin_S chemin_T;

typedef struct case_S case_T;
typedef enum case_E case_E;

typedef union case_U case_U;

/*
enum case_E{
    VIDE,
    BORDURE,
    CHEMIN,
};
*/

union case_U{
    bordure_T *bordure;
    chemin_T *chemin;
};

/**
struct case_S{
    case_E type;
    case_U data;
};
*/
#endif