/**
 * \file menu.h
 * \author meo (meo.prn@outlook.fr)
 * \brief menu du jeux
 * \version 0.1.0
 * \date 2023-03-24
 * 
 */
#ifndef MENU_H
#define MENU_H

#include "../include/init_supr_sdl.h"
#include "../include/interaction_souris.h"
#include "../include/struct_sdl.h"
#include "../include/jeux.h"

/**
 * \brief fonction qui affiche le menu et lance le jeux
 * 
 * \return int 0 si tout c'est bien passé 1 sinon
 */
extern
int menu();

#endif