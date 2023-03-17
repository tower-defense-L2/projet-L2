#include "../include/init_supr_sdl.h"
int main(){
    pack_t * fenetre = malloc(sizeof(pack_t));
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Texture * texture_fond = malloc(sizeof(texture_t));
    SDL_Texture * texture_fond2 = malloc(sizeof(texture_t));

    SDL_Rect win = {0, 0, 0, 0};
    SDL_Rect dst = {0, 0, 0, 0};

    /**
     * \brief Initialisation de la SDL avec gestion d'erreur
     */
    if(intilalisation_sdl()){
        return 1;
    }
    fenetre = creation_pack("test multitexture", 800, 600, SDL_WINDOW_SHOWN, 30);
    if(fenetre == NULL){
        return 1;
    }
    if(load_bitmap("./ressources/test/font.bmp", &texture_fond, fenetre)){
        return 1;
    }

    if(load_bitmap("./ressources/test/font2.bmp", &texture_fond2, fenetre)){
        return 1;
    }

    while(program_launched){
        // debut du cronometre
        Uint64 start = SDL_GetPerformanceCounter();
        SDL_RenderClear(fenetre->renderer);
        /**
         * \brief Gestion des evenements
         */
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            default:
                dst.h = 0; dst.w = 0; dst.x = 0; dst.y = 0;
                SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
                dst.w = win.w/2;
                dst.h = win.h/2;
                SDL_RenderCopy(fenetre->renderer, texture_fond, NULL, &dst);
                dst.x = dst.w;
                SDL_RenderCopy(fenetre->renderer, texture_fond2, NULL, &dst);
                dst.y = dst.h;
                SDL_RenderCopy(fenetre->renderer, texture_fond, NULL, &dst);
                dst.x = 0;
                SDL_RenderCopy(fenetre->renderer, texture_fond2, NULL, &dst);
                break;
        }
        SDL_RenderPresent(fenetre->renderer);

        /**
         * \brief Gestion du temps d'attente pour avoir 60 fps
         */
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(1000/60 - elapsed);
    }
    SDL_DestroyTexture(texture_fond);
    SDL_DestroyTexture(texture_fond2);
    supression_sdl(fenetre);
}