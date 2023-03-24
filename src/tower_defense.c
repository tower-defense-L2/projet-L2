/**
 * \file tower_defence.c
 * \author meo (meo.prn@outlook.fr)
 * \brief fichier principal du jeu tower defence
 * \version 0.1.0
 * \date 2023-03-24
 * 
 */

#include "../include/init_supr_sdl.h"
#include "../include/menu.h"

int main(){
    /**
     * \brief Initialisation de la SDL avec gestion d'erreur
     */
    if(initilalisation_sdl()){
        return 1;
    }
    
    /**
     * \brief appel du menu principal avec gestion d'erreur
    */
    if (menu()){
        return 1;
    }

    /**
     * \brief suppresion de la SDL
     */
    supression_sdl();
    return 0;
}