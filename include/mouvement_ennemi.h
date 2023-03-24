
/**
 * \file mouvement_ennemi.h
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \brief vérifie la possiblité de déplacement d'une bille
 * \version 0.1
 * \date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "stdlib.h"
#include "const.h"
#include "struct.h"

/**
 * \brief vérifie si la bille peux aller sur la case suivante et l'y met si tel est le cas.
 * 
 * \param chemin // Le type de case ou les ennemis peuvent se déplacer
 * \return int int 0 si impossible / 1 si possible
 */
int mouvement_bille(chemin_T *chemin);