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
 * \brief fonction servant à initialiser la sdl, la fenetre et le renderer
 * 
 * \param fenetre // pointeur sur la fenetre 
 * \param renderer // pointeur sur le renderer
 * \return int 
 */
int intilalisation_sdl(fenetre_t *fenetre);

/**
 * \brief fonction servant à stopper la sdl, la fenetre et le renderer
 * 
 * \param fenetre // pointeur sur la fenetre
 * \param renderer // pointeur sur le renderer 
 */
void supression_sdl(fenetre_t *fenetre);

/**
 * \brief fonction servant à charger une bitmap et la convertir en texture
 * 
 * \param path // chemin de la bitmap
 * \param texture // pointeur sur la texture
 * \param renderer // pointeur sur le renderer
 * \return int 
 */
int load_bitmap(char *path, texture_t *texture, fenetre_t *fenetre);

/**
 * \brief fonction servant à supprimer une texture
 * 
 * \param texture // pointeur sur la texture
 */
void supression_texture(texture_t *texture);

/**
 * \brief fonction servant à supprimer une liste de texture
 * 
 * \param texture // pointeur sur l'en tête de la liste
 */
void supression_texture_list(texture_t *texture);


#endif