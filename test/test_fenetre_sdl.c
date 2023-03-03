#include <stdio.h>
#include <SDL2/SDL.h>

int main(){
    SDL_Window* fenetre = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    SDL_bool program_launched = SDL_TRUE;
    SDL_Surface * fond = NULL;
    SDL_Texture * texture_fond = NULL;

    SDL_Rect dst = {0, 0, 0, 0};

    /**
     * \brief Initialisation de la SDL avecc gestion d'erreur
     * 
     */
    if(SDL_VideoInit(NULL) < 0){
        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }


    /**
     * \brief Création de la fenêtre
     * 
     */
    fenetre = SDL_CreateWindow("test_SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_RESIZABLE);
    /**
     * \brief Gestion d'erreur de la fenêtre
     * 
     */
    if(fenetre == NULL){ 
        printf("Erreur de création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /** 
     * \brief création du renedrer
     * 
     */
    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    /**
     * \brief gestion d'erreur du renderer
     * 
     */
    if(renderer == NULL){
        printf("Erreur de création du renderer : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /**
     * \brief load de la bitmap
     * 
     */
    fond = SDL_LoadBMP("./ressources/font.bmp");
    /**
     * \brief gestion d'erreur du load
     * 
     */
    if(fond == NULL){
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /**
     * \brief création de la texture
     * 
     */
    texture_fond = SDL_CreateTextureFromSurface(renderer, fond);
    /**
     * \brief gestion d'erreur de la texture
     * 
     */
    if(texture_fond == NULL){
        printf("Erreur de création de la texture : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }
    /**
     * \brief libération de la surface
     * 
     */
    SDL_FreeSurface(fond);
    fond = NULL;


    /**
     * \brief Affichage de la texture
     * 
     */
    SDL_QueryTexture(texture_fond, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture_fond, NULL, &dst);
    SDL_RenderPresent(renderer);



    /**
     * \brief Création de la boucle d'affichage
     * 
     */
    
    while(program_launched){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
        }
        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}