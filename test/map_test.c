#include "../include/jeux.h"
#include "../include/init_supr_sdl.h"
typedef enum map_type_e { CHEMIN, BORDURE, BILLE, TOUR} map_type_t;

typedef struct map_s{
    map_type_t type;
} map_t;

int main(){
    pack_t * fenetre = NULL;
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Texture * texture_menu = NULL;
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
    SDL_RenderCopy(fenetre->renderer,texture_menu,NULL,NULL);
    SDL_RenderPresent(fenetre->renderer);

    map_type_t map[16][9];
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 9; j++){
            map[i][j] = CHEMIN;
        }
    }
    for(int i = 0; i < 16; i++){
        map[i][0] = BORDURE;
        map[i][8] = BORDURE;
    }
    
}