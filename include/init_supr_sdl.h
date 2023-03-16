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

/**
 * \brief structure contenant la fenetre et le renderer
 */
typedef struct fenetre_s{
    SDL_Window *fenetre; // pointeur sur la fenetre
    SDL_Renderer *renderer; // pointeur sur le renderer
}fenetre_t;


/**
 * \brief structure contenant une texture et un pointeur sur la texture suivante
 */
typedef struct texture_s{
    SDL_Texture *texture; // pointeur sur la texture
    struct texture_s *suivant; // pointeur sur la texture suivante
    struct texture_s *precedent; // pointeur sur la texture précédente
}texture_t;

/**
 * \brief fonction d'initialation de la sdl avec creation de la fenetre et du renderer
 * 
 * \param fenetre structure contenant un poiteur sur le rederer et la fenetre
 * \return int debugage
 */
extern
int intilalisation_sdl(fenetre_t *fenetre);

/**
 * \brief fonction d'arret de la sdl avec destruction de la fenetre et du renderer
 * 
 * \param fenetre structure contenant un poiteur sur le rederer et la fenetre
 */
extern
void supression_sdl(fenetre_t *fenetre);

/**
 * \brief fonction servant à charger une bitmap et la convertir en texture
 * 
 * \param path // chemin de la bitmap
 * \param texture // structure devant contenir la structure
 * \param fenetre // structure contenant le renderer
 * \return int 
 */
extern
int load_bitmap(const char *path, texture_t *texture, fenetre_t *fenetre);

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


#endif