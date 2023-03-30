/**
 * \file map.h
 * \author Antoine Sainty (Sainty.Antoine.Etu@univ-lemans.fr)
 * \brief Fichier contenant les fonctions de gestion de la map
 * \version 0.1.0
 * \date 30/03/2023
 */
#ifndef TOWER_DEFENSE_MAP_H
#define TOWER_DEFENSE_MAP_H

#include <struct.h>

/**
 * \brief Génère la map
 * \param seed La graine de génération de la map
 * \param start La position de départ
 * \param end La position d'arrivée
 */
void generate_map(unsigned int seed, position_T start, position_T end, void (*callback)(map_T*, position_T));

/**
 * \brief Détruit la map
 */
void destroy_map();

/**
 * \brief Vérifie si la map est initialisée
 * \return 1 si la map est initialisée, 0 sinon
 */
int map_initialized();

/**
 * \brief Récupère la map
 * \return La map
 */
map_T *get_map();

/**
 * \brief Récupère une case de la map
 * \param x La position x de la case
 * \param y La position y de la case
 * \return La case
 */
case_T *get_case(int x, int y);

/**
 * \brief Récupère la graine de génération de la map
 * \return La graine de génération de la map
 */
int get_seed();

#endif //TOWER_DEFENSE_MAP_H
