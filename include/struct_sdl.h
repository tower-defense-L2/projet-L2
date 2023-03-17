/**
 * \file struct_sdl.h
 * \author meo (meo.prn@outlook.fr)
 * \brief definition des differente structure utilisé dans le programme pour la SDL
 * \version 0.1.0
 * \date 2023-03-17
 * 
 */

#ifndef STRUCT_SDL_H
#define STRUCT_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * \brief structure contenant la fenetre et le renderer
 */
typedef struct pack_s{
    SDL_Window *fenetre; // pointeur sur la fenetre
    SDL_Renderer *renderer; // pointeur sur le renderer
    TTF_Font *police; // pointeur sur la police
}pack_t;


/**
 * \brief structure contenant une texture et un pointeur sur la texture suivante
 */
typedef struct texture_s{
    SDL_Texture *texture; // pointeur sur la texture
    struct texture_s *suivant; // pointeur sur la texture suivante
    struct texture_s *precedent; // pointeur sur la texture précédente
}texture_t;


/**
 * \brief structure contenant les deux textures d'un bouton (avec et sans souris dessus) plus le rectangle de destination
 */
typedef struct bouton_s{
    SDL_Rect dst;
    SDL_Texture *normale;
    SDL_Texture *survol;
}bouton_t;


#endif