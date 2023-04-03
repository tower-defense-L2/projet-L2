/**
 * \file file.h
 * \author Antoine Sainty (Sainty.Antoine.Etu@univ-lemans.fr)
 * \brief Fichier contenant les fonctions de gestion de la file
 * \version 0.1.0
 * \date 30/03/2023
 */
#ifndef TOWER_DEFENSE_FILE_H
#define TOWER_DEFENSE_FILE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Represent un élément de la file
 */
typedef struct element_S {
    void *data; // Données de l'élément
    struct element_S *next; // Pointeur vers l'élément suivant
} element_T;
/**
 * \brief Représente une file
 */
typedef struct file_S {
    element_T *first; // Pointeur vers le premier élément
    element_T *queue; // Pointeur vers le second élément
    int length; // Longueur de la file
} file_T;

/**
 * \brief Initialise une file
 * \param file La file à initialiser
 */
void file_init(file_T *file);

/**
 * \brief Ajoute un élément à la file
 * \param file La file
 * \param data Les données de l'élément
 */
void file_push(file_T *file, void *data);

/**
 * \brief Récupère le premier élément de la file
 * \param file La file
 * \return Le premier élément de la file
 */
void *file_pop(file_T *file);

/**
 * \brief Récupère le premier élément de la file sans le supprimer
 * \param file La file
 * \return Le premier élément de la file
 */
void *file_peek(file_T *file);

/**
 * \brief Vérifie si la file est vide
 * \param file La file
 * \return 1 si la file est vide, 0 sinon
 */
int file_is_empty(file_T *file);

/**
 * \brief Vide la file
 * \param file La file
 */
void file_clear(file_T *file);

/**
 * \brief Récupère la longueur de la file
 * \param file La file
 * \return La longueur de la file
 */
int file_length(file_T *file);

/**
 * \brief Affiche la file
 * \param file La file
 * \param callback La fonction de callback
 */
void file_print(file_T *file, void (*callback)(void *));

#endif //TOWER_DEFENSE_FILE_H
