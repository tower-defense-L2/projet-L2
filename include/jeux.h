/**
 * \file jeux.h
 * \author meo (meo.prn@outlook.fr)
 * \brief fonction principale du jeu
 * \version 0.1.0
 * \date 2023-03-17
 */
#ifndef JEUX_H
#define JEUX_H

#include <SDL2/SDL.h>
#include "./struct_sdl.h"
#include "./struct.h"
#include "./const.h"
#include "./interaction_souris.h"
#include "./init_supr_sdl.h"

/**
 * \brief fonction principale du jeu
 * 
 * \param fenetre pack_t de la fenetre
 * \return int 1 si tout c'est bien passé 0 sinon
 */
extern
int jeux(pack_t * fenetre);

#endif