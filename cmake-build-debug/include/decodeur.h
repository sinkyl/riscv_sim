#ifndef PROJET1_DECODEUR_H
#define PROJET1_DECODEUR_H

#include <stdint.h>
#include <stdlib.h>
#include "instruction.h"

/** Fonction pour interface externe
 * permet de creer un tableau d instructions a partir de nom du fichier code machine
 * @param chemin_fichier
 * @return le pointeur du tableau d instructions, si le fichier ne peut pas ouvrir
 * return NULL
 */
t_instruction_bloc *assemblage_instructions(char *nom_fichier);

/**
 * Permet de décoder toutes les instruction qui sont dant un tableau
 * d'insctructions.
 * @param instruction     : le tableau d'instructions
 * @param nb_instructions : le nombre d'instruction dans le tableau
 */
void decode_tableau_instructions(t_instruction *instruction, int nb_instructions);

#endif //PROJET1_DECODEUR_H
