#include "../include/init_supr_sdl.h"
#include "../include/menu.h"

int main(){
    //Initialisation de la SDL avec gestion d'erreur
    if(!initilalisation_sdl()){
        return 1;
    }
    
    //appel du menu principal avec gestion d'erreur
    if (!menu()){
        return 1;
    }

    //suppresion de la SDL
    supression_sdl();
    return 0;
}