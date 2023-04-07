
/**
 * \file mouvement_ennemi.h
 * \author Nathan (Nathan.Duval.Etu@univ-lemans.fr)
 * \brief vérifie la possiblité de déplacement d'une bille
 * \version 0.1
 * \date 2023-03-22
 * 
 * 
 */

#ifndef MOUVEMENT_ENNEMI_H
#define MOUVEMENT_ENNEMI_H
#include <stdlib.h>
#include "const.h"
#include "struct.h"

/**
 * \brief vérifie si la bille peux aller sur la case suivante et l'y met si tel est le cas.
 * 
 * \param chemin // Le type de case ou les ennemis peuvent se déplacer
 * \return int int 0 si impossible / 1 si possible
 */
extern
int mouvement_bille(chemin_T *chemin);

/**
 * \brief détruit une bille dont l'id est donné en paramètre
 * 
 * \param id id de la bille à détruire
 */
extern
void detruire_enemi(int id);

/**
 * \brief détruit toutes les billes
 * 
 */
extern
void detruire_enemis();

/**
 * \brief crée une bille avec les paramètres donnés en position -1 -1 et l'ajoute à la liste des billes
 * 
 * \param vie vie de la bille
 * \param reconpense argent gagné en tuant la bille
 * \param vitesse fréquence de déplacement de la bille en s/60
 * \param degat dégat de la bille
 */
extern
void creer_enemi(int vie, int reconpense, int vitesse, int degat);

/**
 * \brief crée une vague d'ennemis en augmentant la difficulté avec le numéro de la vague
 * 
 * \param num_vague numéro de la vague
 */
extern
void creer_vague(int num_vague);

/**
 * \brief vérifie si toutes les billes sont détruites
 * 
 * \return int 1 si toutes les billes sont détruites / 0 sinon
 */
extern
int vague_terminee();
#endif