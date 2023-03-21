#include "../include/jeux.h"

void jeux(){
    SDL_Rect win= {0,0,0,0};
    pack_t * fenetre = creation_pack("Jeu", 800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP |SDL_WINDOW_BORDERLESS, 30);
    
    SDL_SetWindowResizable(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowBordered(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowPosition(fenetre->fenetre, 0, 0);
    SDL_GetDisplayBounds(0,&win);
    SDL_SetWindowSize(fenetre->fenetre, win.w, win.h);

    SDL_Texture * texture = NULL;
    
    load_bitmap("./ressources/test/font2.bmp",&texture,fenetre);
    SDL_RenderCopy(fenetre->renderer,texture,NULL,NULL);
    SDL_RenderPresent(fenetre->renderer);
    SDL_RenderClear(fenetre->renderer);

        
    
    SDL_Delay(5000);
    SDL_DestroyTexture(texture);
    texture = NULL;
    supression_pack(&fenetre);
}