/**
 * \file jeux.c
 * \author meo (meo.prn@outlook.fr)
 * \brief boucle de jeu
 * \version 0.1.0
 * \date 2023-03-22
 * 
 * 
 */
#include "../include/jeux.h"

void jeux(){
    /**
     * \brief création de la fenetre
     */
    SDL_Rect win= {0,0,0,0};
    pack_t * fenetre = creation_pack("Jeu", 1600, 900, SDL_WINDOW_FULLSCREEN_DESKTOP |SDL_WINDOW_BORDERLESS, 30);
    /**
     * \brief verrouillage de la fenetre en plein écran 
     */
    SDL_SetWindowResizable(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowBordered(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowPosition(fenetre->fenetre, 0, 0);
    SDL_GetDisplayBounds(0,&win);
    SDL_SetWindowSize(fenetre->fenetre, win.w, win.h);

    /**
     * \brief initialisation des variables
     */
    SDL_Texture * texture = NULL;
    
    /**
     * \brief chargement de l'image de fond et gestion d'erreur
     */
    if(load_bitmap("./ressources/font.bmp",&texture,fenetre)){
        return;
    }



    SDL_RenderCopy(fenetre->renderer,texture,NULL,NULL);
    SDL_RenderPresent(fenetre->renderer);
    SDL_RenderClear(fenetre->renderer);

        
    
    SDL_Delay(5000);

    /**
     * \brief destruction de la texture
     * 
     */
    SDL_DestroyTexture(texture);
    texture = NULL;
    /**
     * \brief fermeture de la fenetre de jeu
     */
    supression_pack(&fenetre);
}