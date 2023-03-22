/**
 * \file struct_sdl.h
 * \author meo (meo.prn@outlook.fr)
 * \brief definition des differente structure utilisé par les fonctions de sdl
 * \version 0.1.0
 * \date 2023-03-17
 * 
 */

#ifndef STRUCT_SDL_H
#define STRUCT_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/**
 * \brief primitive de la structure pack_t
 */
typedef struct pack_s{
    SDL_Window *fenetre; 
    SDL_Renderer *renderer; 
    TTF_Font *police;
}pack_t;
/** 
 * \struct pack_t
 * \brief structure contenant les pointeurs sur la fenetre, le renderer et la police
 * \param *fenetre pointeur sur la fenetre
 * \param *renderer pointeur sur le renderer
 * \param *police pointeur sur la police
*/


/**
 * \brief primitive de la structure texture_t
 */
typedef struct texture_s{
    SDL_Texture *texture;
    struct texture_s *suivant;
    struct texture_s *precedent;
}texture_t;
/**
 * \struct texture_t
 * \brief structure contenant les pointeurs sur la texture et les pointeurs sur les textures suivantes et précédentes
 * \param *texture pointeur sur la texture
 * \param *suivant pointeur sur la texture_t suivante
 * \param *precedent pointeur sur la texture_t précédente
 */


/**
 * \brief primitive de la structure bouton_t
 */
typedef struct bouton_s{
    SDL_Rect dst; 
    SDL_Texture *normale; 
    SDL_Texture *survol; 
}bouton_t;
/**
 * \struct bouton_t
 * \brief structure contenant le rectangle contenant le bouton et les pointeurs sur les textures du bouton
 * 
 * \param dst rectangle taille et position du bouton
 * \param *normale pointeur sur la texture normale
 * \param *survol pointeur sur la texture survol
 * 
 */


#endif