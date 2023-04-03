#include "../include/mouvement_ennemi.h"

extern
int mouvement_bille(chemin_T *chemin)
{

    //vérifie que la case suivante est libre
    if (chemin->suivant->enemi == NULL)
    {
        chemin->enemi->position = chemin->suivant->position; // met la bille sur la case suivante
        chemin->suivant->enemi = NULL;
        chemin->enemi = NULL;
        return 1;
    }

    return 0;
}

