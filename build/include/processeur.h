#ifndef PROJET1_PROCESSEUR_H
#define PROJET1_PROCESSEUR_H

#include "decodeur.h"
#include "instruction.h"

/**
 * Structure qui permet de simuler un processeur RISC V RV32EM
 * Propriétés:
 *      nb_structure: représente le nombre d'instruction qu'il contient
 *      nb_instruction_executees: à la X ème instruction
 *      pc: représente l'instruction actuelle exécutée
 *      intructions: C'est le tableau des instructions
 *      registres: Un tableau de 16 registres
 *      mémoire: tableau de mémoire
 */
typedef struct
{
    int nb_instructions;
    int nb_instructions_executees;
    uint32_t pc;
    t_instruction *instructions;

    int32_t registres[16];
    uint8_t memoire[16777216]; //memoire d'une gandeur de 2^24

} t_processeur;

/**
 * Permet de créer une instance du processeur.
 * @return le pointeur de la structure processeur alloué
 */
t_processeur *creer_processeur(void);


/**
 * Met les valeurs dans le registre à 0.
 * @param registre tableau de registre signé 32 bits
 */
void remise_a_zero_registre(int32_t *registre);


/**
 * Charge un octet de la mémoire à l'adresse x[rs1] + signe(imm) et
 * l'écrit dans x[rd] qui est signé.
 * @param instruction a executer
 * @param registres du processeur
 * @param memoire du processeur
 */
void load_byte(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire);


/**
 *Charge un octet de la mémoire à l'adresse x[rs1] + signe(imm)
 * et un autre l'adresse x[rs1+1] + signe(imm) pour former 16bits
 * et l'écrire dans x[rd] qui est signé.
 * @param instruction a executer
 * @param registres du processeur
 * @param memoire du processeur
 */
void load_halfword(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire);


/**
 *Charge un octet de la mémoire à l'adresse x[rs1] + signe(imm),
 * un autre l'adresse x[rs1+1] + signe(imm),
 * un autre l'adresse x[rs1+2] + signe(imm),
 * un autre l'adresse x[rs1+3] + signe(imm), pour former 32bits
 * et l'écrire dans x[rd] qui est signé.
 * @param instruction a executer
 * @param registres du processeur
 * @param memoire du processeur
 */
void load_word(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire);


/**
 * Charge un octet de la mémoire à l'adresse x[rs1] + signe(imm) et
 * l'écrit dans x[rd] qui est non signé.
 * @param instruction a executer
 * @param registres du processeur
 * @param memoire du processeur
 */
void load_byte_unsigned(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire);


/**
 *Charge un octet de la mémoire à l'adresse x[rs1] + signe(imm)
 * et un autre l'adresse x[rs1+1] + signe(imm) pour former 16bits
 * et l'écrire dans x[rd] qui est non signé.
 * @param instruction a executer
 * @param registres du processeur
 * @param memoire du processeur
 */
void load_halfword_unsigned(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire);


/**
 *Charge un octet du registre x[rs2] et l'ecrit en memoire a l'adresse
 * x[rs1]+signe(imm)
 * @param instruction a executer
 * @param registres du processeur
 * @param memoire du processeur
 */
void store_byte(
        t_instruction *instruction, const int32_t *registres,
        uint8_t *memoire);


/**
 *Charge 16bits du registre x[rs2] et l'ecrit en memoire a l'adresse
 * x[rs1]+signe(imm) octet1, x[rs1+1]+signe(imm) octet2
 * @param registres du processeur
 * @param memoire du processeur
 */
void store_half_word(
        t_instruction *instruction, const int32_t *registres,
        uint8_t *memoire);


/**
 *Charge 32bits du registre x[rs2] et l'ecrit en memoire a l'adresse
 * x[rs1]+signe(imm) octet1, x[rs1+1]+signe(imm) octet2
 * x[rs1+2]+signe(imm) octet3, x[rs1+3]+signe(imm) octet4
 * @param instruction a executer
 * @param registres du processeur
 * @param memoire du processeur
 */
void store_word(
        t_instruction *instruction, const int32_t *registres,
        uint8_t *memoire);


/**
 *Decalage des bits vers la gauche du registre[rs1] et inscrire le
 * resultat dans registre[rd] , nb_bits de a decaler est indiquer dans
 * registre[rs2] (5 bits les moins significatifs)
 * @param instruction a executer
 * @param registre du processeur
 */
void shift_left(t_instruction *instruction, int32_t *registre);


/**
 *Decalage des bits vers la gauche du registre[rs1] et inscrire le
 * resultat dans registre[rd] , nb_bits de a decaler est indiquer dans
 * immediat (5 bits les moins significatifs)
 * @param instruction a executer
 * @param registre du processeur
 */
void shift_left_immediate(t_instruction *instruction, int32_t *registre);


/**
 *Decalage des bits vers la droite du registre[rs1] et inscrire le
 * resultat dans registre[rd] , nb_bits de a decaler est indiquer dans
 * registre[rs2] (5 bits les moins significatifs)
 * @param instruction a executer
 * @param registre du processeur
 */
void shift_right(t_instruction *instruction, int32_t *registre);


/**
 *Decalage des bits vers la droite du registre[rs1] et inscrire le
 * resultat dans registre[rd] , nb_bits de a decaler est indiquer dans
 * immediat (5 bits les moins significatifs)
 * @param instruction a executer
 * @param registre du processeur
 */
void shift_right_immediate(t_instruction *instruction, int32_t *registre);


/**
 *Decalage des bits vers la droite du registre[rs1] et inscrire le
 * resultat dans registre[rd] + extend le signe orignial, nb_bits de
 * a decaler est indiquer dans registre[rs2] (5 bits les moins significatifs)
 * @param instruction a executer
 * @param registre du processeur
 */
void shift_right_arith(t_instruction *instruction, int32_t *registre);


/**
 *Decalage des bits vers la droite du registre[rs1] et inscrire le
 * resultat dans registre[rd] + extend le signe orignial, nb_bits de
 * a decaler est indiquer dans immediat (5 bits les moins significatifs)
 * @param instruction a executer
 * @param registre du processeur
 */
void shift_right_arith_immediate(t_instruction *instruction, int32_t *registre);


/**
 * Additionne x[Rs1] à x[Rs2] et
 * l'enregistre dans le registre destination
 * @param instruction
 * @param registre
 */
void addition(t_instruction *instruction, int32_t *registre);


/**
 * Additionne x[Rs1] à la valeur immédiat et
 * l'enregistre dans le registre destination
 * @param instruction
 * @param registre
 */
void addition_immediate(t_instruction *instruction, int32_t *registre);


/**
 * Soustrait x[Rs1] par x[Rs2] et l'enregistre dans le registre destination
 * @param instruction
 * @param registre
 */
void subtract(t_instruction *instruction, int32_t *registre);


/**
 * Entre fans le registre destination la valeur immédiat
 * @param instruction
 * @param registre
 */
void load_upper_immediate(t_instruction *instruction, int32_t *registre);


/**
 * Entre dans le registre destination le pc + l'immédiat afin d'obtenir
 * une instruction suivante relative au pc présent
 * @param instruction
 * @param registre
 */
void add_upper_imm_to_pc(
        t_instruction *instruction, int32_t *registre,
        uint32_t *pc);


/**
 * Entre dans destination le résultat de
 * Bitwise xor entre x[Rs1] et x[Rs2]
 * @param instruction
 * @param registre
 */
void xor(t_instruction *instruction, int32_t *registre);


/**
 * Entre dans destination le résultat de
 * Bitwise xor entre x[Rs1] et immediat
 * @param instruction
 * @param registre
 */
void xor_immediate(t_instruction *instruction, int32_t *registre);


/**
 * Entre dans destination le résultat de
 * Bitwise or entre x[Rs1] et x[Rs2]
 * @param instruction
 * @param registre
 */
void or(t_instruction *instruction, int32_t *registre);


/**
 * Entre dans destination le résultat de
 * Bitwise or entre x[Rs1] et immediat
 * @param instruction
 * @param registre
 */
void or_immediate(t_instruction *instruction, int32_t *registre);


/**
 * Entre dans destination le résultat de
 * Bitwise and entre x[Rs1] et x[Rs2]
 * @param instruction
 * @param registre
 */
void and(t_instruction *instruction, int32_t *registre);


/**
 * Entre dans destination le résultat de
 * Bitwise and entre x[Rs1] et immediat
 * @param instruction
 * @param registre
 */
void and_immediate(t_instruction *instruction, int32_t *registre);


/**
 * Set la destination à 1 lorsque x[Rs1] < x[Rs2]
 * sinon set à 0
 * @param instruction
 * @param registre
 */
void set(t_instruction *instruction, int32_t *registre);


/**
 * Set la destination à 1 lorsque x[Rs1] < Immediat
 * sinon set à 0
 * @param instruction
 * @param registre
 */
void set_immediate(t_instruction *instruction, int32_t *registre);


/**
 * Set la destination à 1 lorsque x[Rs1] < x[Rs2]
 * sinon set à 0
 * @param instruction
 * @param registre
 */
void set_unsigned(t_instruction *instruction, int32_t *registre);


/**
 * Set la destination à 1 lorsque (uint)x[Rs1] < (uint)Immediat
 * sinon set à 0
 * @param instruction
 * @param registre
 */
void set_immediate_unsigned(t_instruction *instruction, int32_t *registre);


/**
 * Si x[Rs1] == x[Rs2], augmente pc à pc+immédiat
 * Sinon, augmente à la prochaine instruction
 * @param instruction à exécuter
 * @param registre du processeur
 * @param pc contenant la position de l'instruction actuelle
 */
void branch_equal(t_instruction *instruction, int32_t *registre, uint32_t *pc);


/**
 * Si x[Rs1] != x[Rs2], augmente pc à pc+immédiat
 * Sinon, augmente à la prochaine instruction
 * @param instruction à exécuter
 * @param registre du processeur
 * @param pc contenant la position de l'instruction actuelle
 */
void
branch_not_equal(t_instruction *instruction, int32_t *registre, uint32_t *pc);


/**
 * Si x[Rs1] < x[Rs2], augmente pc à pc+immédiat
 * Sinon, augmente à la prochaine instruction
 * @param instruction à exécuter
 * @param registre du processeur
 * @param pc contenant la position de l'instruction actuelle
 */
void
branch_less_than(t_instruction *instruction, int32_t *registre, uint32_t *pc);


/**
 * Si x[Rs1] >= x[Rs2], augmente pc à pc+immédiat
 * Sinon, augmente à la prochaine instruction
 * @param instruction à exécuter
 * @param registre du processeur
 * @param pc contenant la position de l'instruction actuelle
 */
void branch_greater_or_equal(
        t_instruction *instruction,
        int32_t *registre,
        uint32_t *pc);


/**
 * Si (uint)x[Rs1] < (uint)x[Rs2], augmente pc à pc+immédiat
 * Sinon, augmente à la prochaine instruction
 * @param instruction à exécuter
 * @param registre du processeur
 * @param pc contenant la position de l'instruction actuelle
 */
void branch_less_unsigned(
        t_instruction *instruction,
        int32_t *registre,
        uint32_t *pc);


/**
 * Si (uint)x[Rs1] > = (uint)x[Rs2], augmente pc à pc+immédiat
 * Sinon, augmente à la prochaine instruction
 * @param instruction à exécuter
 * @param registre du processeur
 * @param pc contenant la position de l'instruction actuelle
 */
void branch_greater_or_equal_unsigned(
        t_instruction *instruction,
        int32_t *registre,
        uint32_t *pc);


/**
 * Entre le pc vers la prochaine instruction dans le registre destination
 * puis change le pc pour pc + immediat
 * @param instruction à exécuter
 * @param registre du processeur
 * @param pc contenant la position de l'instruction actuelle
 */
void jump_and_link(t_instruction *instruction, int32_t *registre, uint32_t *pc);


/**
 * Entre le pc vers la prochaine instruction dans le registre de destination
 * puis change le pc pour Rs1 + imm et met le LSB à 0
 * @param instruction à exécuter
 * @param registre du processeur
 * @param pc contenant la position de l'instruction actuelle
 */
void jump_and_link_register(
        t_instruction *instruction, int32_t *registre,
        uint32_t *pc);


/**
 * Multipli deux nombres
 * (int)x[Rs1] * (int)x[Rs2]
 * @param instruction à exécuter
 * @param registre du processeur
 */
void multiply(t_instruction *instruction, int32_t *registre);


/**
 * Multipli deux nombres signés dans un 64 bit puis shift de 32 bits
 * (int64)x[Rs1] * (int64)x[Rs2] >>32
 * @param instruction à exécuter
 * @param registre du processeur
 */
void multiply_high(t_instruction *instruction, int32_t *registre);


/**
 * Multipli un nombre non-signé par un nombre signé puis shift de 32 bits
 * (int64)x[Rs1] * (uint64)x[Rs2] >>32
 * @param instruction à exécuter
 * @param registre du processeur
 */
void
multiply_high_unsigned_signed(t_instruction *instruction, int32_t *registre);


/**
 * Multipli deux nombres non-signés puis shift de 32 bits
 * (uint64)x[Rs1] * (uint64)x[Rs2] >>32
 * @param instruction à exécuter
 * @param registre du processeur
 */
void multiply_high_unsigned(t_instruction *instruction, int32_t *registre);


/**
 * Divise deux nombres signés
 * (int)x[Rs1] % (int)x[Rs2]
 * @param instruction à exécuter
 * @param registre du processeur
 */
void divide(t_instruction *instruction, int32_t *registre);


/**
 * Divise deux nombres non-signés
 * (uint)x[Rs1] / (uint)x[Rs2]
 * @param instruction à exécuter
 * @param registre du processeur
 */
void divide_unsigned(t_instruction *instruction, int32_t *registre);


/**
 * Fait un calcul de reste d'une division avec des nombres signés
 * (int)x[Rs1] % (int)x[Rs2]
 * @param instruction à exécuter
 * @param registre du processeur
 */
void remainder_p(t_instruction *instruction, int32_t *registre);


/**
 * Fait un calcul de reste d'une division avec des nombres non-signés
 * (uint)x[Rs1] % (uint)x[Rs2]
 * @param instruction à exécuter
 * @param registre du processeur
 */
void remainder_unsigned(t_instruction *instruction, int32_t *registre);

#endif //PROJET1_PROCESSEUR_H
