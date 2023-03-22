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
 * \brief structure contenant les pointeurs sur la fenetre, le renderer et la police
 */
typedef struct pack_s{
    SDL_Window *fenetre; // pointeur sur la fenetre
    SDL_Renderer *renderer; // pointeur sur le renderer
    TTF_Font *police; // pointeur sur la police
}pack_t;


/**
 * \brief structure contenant les pointeurs sur la texture et les pointeurs sur les textures suivantes et précédentes
 */
typedef struct texture_s{
    SDL_Texture *texture; // pointeur sur la texture
    struct texture_s *suivant; // pointeur sur la texture suivante
    struct texture_s *precedent; // pointeur sur la texture précédente
}texture_t;


/**
 * \brief structure contenant le rectangle contenant le bouton et les pointeurs sur les textures du bouton
 */
typedef struct bouton_s{
    SDL_Rect dst; // rectangle taille et position du bouton
    SDL_Texture *normale; // pointeur sur la texture normale
    SDL_Texture *survol; // pointeur sur la texture survol
}bouton_t;


#endif