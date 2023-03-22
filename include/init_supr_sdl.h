/**
 * \file init_supr_sdl.h
 * \author meo (meo.prn@outlook.fr)
 * \brief différente fonction servant pour la création et la destruction de la sdl
 * \version 0.1.0
 * \date 2023-03-09
 * 
 */

#ifndef INIT_SUPR_SDL_H
#define INIT_SUPR_SDL_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include "./struct_sdl.h"


/**
 * \brief creation d'une fenetre et d'un renderer et chargement de la police
 * 
 * \param titre // titre de la fenetre a creer
 * \param width // largeur de la fenetre
 * \param height // hauteur de la fenetre
 * \param flags // flags de la fenetre
 * \param taille_police // taille de la police
 * \return pack_t* // pointeur sur la structure contenant le renderer, fenetre et police. null si erreur
 */
extern
pack_t * creation_pack(char * titre, int width, int height, int flags, int taille_police);


/**
 * \brief fonction d'initialation de la sdl et ttf
 * 
 * \param fenetre // structure contenant un poiteur sur le rederer et la fenetre
 * \return int // 0 si tout c'est bien passé 1 sinon
 */
extern
int initilalisation_sdl();

/**
 * \brief fonction de destruction d'une fenetre et d'un renderer et de la police
 * 
 * \param fenetre //
 */
extern
void supression_pack(pack_t ** fenetre);

/**
 * \brief fonction d'arret de la sdl et ttf
 * \param fenetre // structure contenant un poiteur sur le rederer et la fenetre
 */
extern
void supression_sdl();

/**
 * \brief fonction servant à charger une bitmap et la convertir en texture
 * 
 * \param path // chemin de la bitmap
 * \param texture // structure devant contenir la structure
 * \param fenetre // structure contenant le renderer
 * \return int // 0 si tout c'est bien passé 1 sinon
 */
extern
int load_bitmap(const char *path, SDL_Texture **texture, pack_t *fenetre);

/**
 * \brief fonction servant à supprimer une texture
 * 
 * \param texture // pointeur sur la structure contenant la texture
 */
extern
void supression_texture(texture_t *texture);

/**
 * \brief fonction servant à supprimer une liste de texture
 * 
 * \param texture // pointeur sur l'en tête de la liste
 */
extern
void supression_texture_liste(texture_t *texture);

/**
 * \brief fonction servant à créer un bouton
 * 
 * \param fenetre // structure contenant le renderer, fenetre et police
 * \param texte // texte du bouton
 * \param couleur // couleur du texte
 * \param wrap // couleur du fond en survol
 * \param x // position x du bouton
 * \param y // position y du bouton
 * \return bouton_t // poiteur sur structure contenant les texture du bouton
 */
extern
bouton_t * creation_bouton(pack_t * fenetre, char * texte,
                SDL_Color couleur, SDL_Color wrap, int x, int y);

/**
 * \brief fonction servant à supprimer un bouton
 * 
 * \param bouton // pointeur sur la structure contenant le bouton
 */
extern
void supression_bouton(bouton_t ** bouton);

/**
 * \brief attribue une position au rectangle du bouton
 * 
 * \param bouton // pointeur sur la structure contenant le bouton
 * \param x // position x du bouton
 * \param y // position y du bouton
 */
extern
void position_bouton(bouton_t * bouton, const int x, const int y);

#endif