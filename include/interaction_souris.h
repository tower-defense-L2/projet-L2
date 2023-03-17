/**
 * \file interaction_souris.h
 * \author meo (meo.prn@outlook.fr)
 * \brief differentes fonctions pour gerer la souris avec SDL
 * \version 0.1.0
 * \date 2023-03-17
 * 
 */

#ifndef INTERACTION_SOURIS_H
#define INTERACTION_SOURIS_H

#include <SDL2/SDL.h>
#include "./struct_sdl.h"

/**
 * \brief verifie si la souris est sur un rectangle
 * 
 * \param x // position x de la souris
 * \param y // position y de la souris
 * \param rect // rectangle a verifier
 * \return int // 1 si la souris est sur le rectangle, 0 sinon
 */
extern
int souris_dessu(const int x, const int y, const SDL_Rect *rect);


/**
 * \brief gere les boutons pour savoir si la souris est dessus ou non
 * 
 * \param bouton // pointeur sur la structure bouton
 * \param fenetre // pointeur sur la structure pack
 * \param x // position x de la souris
 * \param y // position y de la souris
 */
extern
int gestion_bouton(const bouton_t * bouton, pack_t * fenetre , const int x, const int y);

#endif