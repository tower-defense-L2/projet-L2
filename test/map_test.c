#include "../include/jeux.h"
#include "../include/init_supr_sdl.h"
typedef enum map_type_e { CHEMIN_TEST, BORDURE, BILLE, TOUR} map_type_t;

int main(){
    pack_t * fenetre = NULL;
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Texture * texture_menu = NULL;
    SDL_Texture * chemin = NULL;
    SDL_Texture * bordure = NULL;
    SDL_Texture * bille = NULL;
    SDL_Texture * tour = NULL;
    Uint64 start, end;
    float elapsed = 0;
    Uint32 Click = 0; // état du clique
    int x = 0, y = 0; // position de la souris

    SDL_Rect win= {0,0,0,0};
    SDL_Rect tuile= {0,0,0,0};

    SDL_Color coueur_noir = {0,0,0,255};

    initilalisation_sdl();
    fenetre = creation_pack("test map", 800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP |SDL_WINDOW_BORDERLESS, 30);
    SDL_SetWindowResizable(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowBordered(fenetre->fenetre, SDL_FALSE);
    SDL_SetWindowPosition(fenetre->fenetre, 0, 0);
    SDL_GetDisplayBounds(0,&win);
    SDL_SetWindowSize(fenetre->fenetre, win.w, win.h);

    load_bitmap("./ressources/test/font2.bmp",&texture_menu,fenetre);
    load_bitmap("./ressources/chemin.bmp",&chemin,fenetre);
    load_bitmap("./ressources/bordure.bmp",&bordure,fenetre);
    load_bitmap("./ressources/bille.bmp",&bille,fenetre);
    load_bitmap("./ressources/tour.bmp",&tour,fenetre);

    map_type_t map[16][9];
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 9; j++){
            map[i][j] = CHEMIN_TEST;
        }
    }
    for(int i = 0; i < 16; i++){
        map[i][0] = BORDURE;
        map[i][8] = BORDURE;
    }


    map[5][5] = BILLE;
    map[6][6] = TOUR;

    tuile = (SDL_Rect){0, 0, win.w/18, win.h/11};

    
    while(program_launched){
        SDL_GetWindowSize(fenetre->fenetre, &win.w, &win.h);
        start = SDL_GetPerformanceCounter();
        SDL_RenderClear(fenetre->renderer);
        Click = SDL_GetMouseState(&x, &y);
        SDL_RenderCopy(fenetre->renderer, texture_menu, NULL, NULL);

        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 9; j++){
                tuile.x = (i+1) * tuile.w;
                tuile.y = (j+1) * tuile.h;
                switch(map[i][j]){
                    case CHEMIN_TEST:
                        SDL_RenderCopy(fenetre->renderer, chemin, NULL, &tuile);
                        break;
                    case BORDURE:
                        SDL_RenderCopy(fenetre->renderer, bordure, NULL, &tuile);
                        break;
                    case BILLE:
                        SDL_RenderCopy(fenetre->renderer, chemin, NULL, &tuile);
                        SDL_RenderCopy(fenetre->renderer, bille, NULL, &tuile);
                        break;
                    case TOUR:
                        SDL_RenderCopy(fenetre->renderer, bordure, NULL, &tuile);
                        SDL_RenderCopy(fenetre->renderer, tour, NULL, &tuile);
                        break;
                }
            }
        }
        SDL_RenderPresent(fenetre->renderer);
        end = SDL_GetPerformanceCounter();
        elapsed = (end - start) * 1000 / (float)SDL_GetPerformanceFrequency();
        if(elapsed < 1000/60){
            SDL_Delay((1000/60) - elapsed);
        }
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        program_launched = SDL_FALSE;
                        break;
                }
                break;
        }
    }
    
}