#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../include/processeur.h"

/**********************************************************
*                   FONCTIONS PRIVÉES
**********************************************************/
/**
 *
 * @param value
 * @param bitnum
 * @return
 */
uint32_t set_bit(uint32_t value, uint8_t bitnum);


/**********************************************************
*           IMPLÉMENTATION DES FONCTIONS
**********************************************************/

t_processeur *creer_processeur()
{
    t_processeur *processeur;
    processeur = (t_processeur *) malloc(sizeof(t_processeur));

    if (processeur == NULL)
    {
        printf("Erreur d'obtention de la mémoire!");
    }

    processeur->pc = 0;
    processeur->nb_instructions_executees = 0;

    remise_a_zero_registre(processeur->registres);

    return processeur;
}


void remise_a_zero_registre(int32_t *registres)
{
    for (int i = 0; i < 16; i++)
    {
        registres[i] = 0;
    }
}

/*******************************************************************************
*                      LES FONCTIONS DES LOAD                                 */
//
void load_byte(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire)
{
    registres[instruction->registre_destination]
            = (int32_t) (memoire[registres[instruction->registre_source1]
                                 + (int32_t) instruction->immediat]);
}


//
void load_halfword(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire)
{
    uint32_t index = registres[instruction->registre_source1] +
                     (int32_t) instruction->immediat;

    registres[instruction->registre_destination]
            = (int32_t) ((memoire[index] << 8u)
                         + memoire[index + 1]);
}


//
void load_word(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire)
{
    uint32_t index = registres[instruction->registre_source1] +
                     (int32_t) instruction->immediat;

    uint32_t i1 = memoire[index];
    uint32_t i2 = memoire[index + 1];
    uint32_t i3 = memoire[index + 2];
    uint32_t i4 = memoire[index + 3];

    int32_t mot;

    mot = (i1 << 24u);
    mot = (i2 << 16u) + mot;
    mot = (i3 << 8u) + mot;
    mot = mot + i4;
    registres[instruction->registre_destination] = mot;

}


//
void load_byte_unsigned(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire)
{
    registres[instruction->registre_destination]
            = (uint32_t) memoire[registres[instruction->registre_source1]
                                 + (int32_t) instruction->immediat];
}


//
void load_halfword_unsigned(
        t_instruction *instruction, int32_t *registres,
        const uint8_t *memoire)
{
    uint32_t index = registres[instruction->registre_source1] +
                     (int32_t) instruction->immediat;

    registres[instruction->registre_destination]
            = (uint32_t) ((memoire[index] << 8u)
                          + memoire[index + 1]);
}
/******************************************************************************/


/*******************************************************************************
*                       LES FONCTIONS DE STORE                                */
//
void store_byte(
        t_instruction *instruction, const int32_t *registres,
        uint8_t *memoire)
{
    memoire[registres[instruction->registre_source1]
            + (int32_t) instruction->immediat]
            = (registres[instruction->registre_source2] & 0x000000FFu);
}


//
void store_half_word(
        t_instruction *instruction, const int32_t *registres,
        uint8_t *memoire)
{
    int8_t i1 = registres[instruction->registre_source2] & 0x00FFu;
    int8_t i2 = (registres[instruction->registre_source2] >> 8u) & 0x00FFu;

    uint32_t index = registres[instruction->registre_source1] +
                     (int32_t) instruction->immediat;

    memoire[index] = i1;
    memoire[index + 1] = i2;
}


//
void store_word(
        t_instruction *instruction, const int32_t *registres,
        uint8_t *memoire)
{
    int32_t mot = registres[instruction->registre_source2] & 0xFFFFFFFFu;
    int8_t i1 = mot & 0x000000FF;
    int8_t i2 = (mot >> 8u) & 0x000000FFu;
    int8_t i3 = (mot >> 16u) & 0x000000FFu;
    int8_t i4 = (mot >> 24u) & 0x000000FFu;

    uint32_t index = registres[
                             instruction->registre_source1] +
                     (int32_t) instruction->immediat;

    memoire[index] = i1;
    memoire[index + 1] = i2;
    memoire[index + 2] = i3;
    memoire[index + 3] = i4;
}
/******************************************************************************/


/*******************************************************************************
*                       LES FONCTIONS DE SHIFT                                */
//
void shift_left(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (int32_t) ((uint32_t) registre[instruction->registre_source1]
                    << ((uint32_t) registre[instruction->registre_source2] &
                        0x1Fu));
}


//
void shift_left_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (int32_t) ((uint32_t) registre[instruction->registre_source1]
                    << ((int32_t) instruction->immediat & 0x1Fu));
}


//
void shift_right(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (int32_t) ((uint32_t) registre[instruction->registre_source1]
                    >> ((uint32_t) registre[instruction->registre_source2] &
                        0x1Fu));
}


//
void shift_right_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (int32_t) ((uint32_t) registre[instruction->registre_source1]
                    >> (uint32_t) ((int32_t) instruction->immediat & 0x1Fu));
}


//
void shift_right_arith(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (int32_t) ((uint32_t) registre[instruction->registre_source1]
                    >> ((uint32_t) registre[instruction->registre_source2] &
                        0x1Fu));
    if (registre[instruction->registre_source1] >> 31 != 0)
    {
        for (int i = 0;
             i < (registre[instruction->registre_source2] & 0x1Fu); i++)
        {
            registre[instruction->registre_destination] = set_bit(
                    registre[instruction->registre_destination], 31 - i);
        }
    }
}


//
void shift_right_arith_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (int32_t) ((uint32_t) registre[instruction->registre_source1]
                    >> ((int32_t) instruction->immediat & 0x1Fu));
    if (registre[instruction->registre_source1] >> 31 != 0)
    {
        for (int i = 0; i < ((int32_t) instruction->immediat & 0x1Fu); i++)
        {
            registre[instruction->registre_destination] = set_bit(
                    registre[instruction->registre_destination], 31 - i);
        }
    }
}
/******************************************************************************/


/*******************************************************************************
*                      LES FONCTIONS DE ARITHMETIQUE                          */
//
void addition(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] +
            registre[instruction->registre_source2];
}


//
void addition_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] +
            (int32_t) instruction->immediat;
}


//
void subtract(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] -
            registre[instruction->registre_source2];
}


//
void load_upper_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] = (int32_t) instruction->immediat;
    //immediat deja envoyer comme il faut par le decodeur
}


//
void add_upper_imm_to_pc(
        t_instruction *instruction, int32_t *registre,
        uint32_t *pc)
{

    registre[instruction->registre_destination] =
            ((*pc)*4) + (int32_t)((((uint32_t)instruction->immediat) & 0xFFFFF000u));

//    registre[instruction->registre_destination] =
//            *pc + (int32_t) instruction->immediat / 4;
    //immediat deja envoyer comme il faut par le decodeur
}
/******************************************************************************/


/*******************************************************************************
*                      LES FONCTIONS DE LOGIQUES                              */
//
void xor(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] ^
            registre[instruction->registre_source2];
}


//
void xor_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] ^
            (int32_t) instruction->immediat;
}


//
void or(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] |
            registre[instruction->registre_source2];
}


//
void or_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] |
            (int32_t) instruction->immediat;
}


//
void and(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] &
            registre[instruction->registre_source2];
}


//
void and_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] &
            (int32_t) instruction->immediat;
}
/******************************************************************************/


/*******************************************************************************
*                      LES FONCTIONS DE COMPARAISONS                          */
//
void set(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] <
            registre[instruction->registre_source2];
}


//
void set_immediate(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (registre[instruction->registre_source1] <
             (int32_t) instruction->immediat);
}


//
void set_unsigned(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (uint32_t) registre[instruction->registre_source1] <
            (uint32_t) registre[instruction->registre_source2];
}


//
void set_immediate_unsigned(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (uint32_t) registre[instruction->registre_source1] <
            (uint32_t) instruction->immediat;
}
/******************************************************************************/


/*******************************************************************************
*                      LES FONCTIONS DE BRANCHES                              */
//
void branch_equal(t_instruction *instruction, int32_t *registre, uint32_t *pc)
{
    if (registre[instruction->registre_source1] ==
        registre[instruction->registre_source2])
    {
        *pc = *pc + (int32_t) instruction->immediat / 4;
    }
    else
    {
        *pc = *pc + 1;
    }
}


//
void
branch_not_equal(t_instruction *instruction, int32_t *registre, uint32_t *pc)
{
    if (registre[instruction->registre_source1] !=
        registre[instruction->registre_source2])
    {
        *pc = *pc + (int32_t) instruction->immediat / 4;
    }
    else
    {
        *pc = *pc + 1;
    }
}


//
void
branch_less_than(t_instruction *instruction, int32_t *registre, uint32_t *pc)
{
    if (registre[instruction->registre_source1] <
        registre[instruction->registre_source2])
    {
        *pc = *pc + (int32_t) instruction->immediat / 4;
    }
    else
    {
        *pc = *pc + 1;
    }
}


//
void branch_greater_or_equal(
        t_instruction *instruction,
        int32_t *registre,
        uint32_t *pc)
{
    if ((int32_t) registre[instruction->registre_source1] >=
        (int32_t) registre[instruction->registre_source2])
    {
        *pc = *pc + (int32_t) instruction->immediat / 4;
    }
    else
    {
        *pc = *pc + 1;
    }
}


//
void branch_less_unsigned(
        t_instruction *instruction,
        int32_t *registre,
        uint32_t *pc)
{
    if ((uint32_t) registre[instruction->registre_source1] <
        (uint32_t) registre[instruction->registre_source2])
    {
        *pc = *pc + (int32_t) instruction->immediat / 4;
    }
    else
    {
        *pc = *pc + 1;
    }
}


//
void branch_greater_or_equal_unsigned(
        t_instruction *instruction,
        int32_t *registre,
        uint32_t *pc)
{
    if ((uint32_t) registre[instruction->registre_source1] >=
        (uint32_t) registre[instruction->registre_source2])
    {
        *pc = *pc + (int32_t) instruction->immediat / 4;
    }
    else
    {
        *pc = *pc + 1;
    }
}
/******************************************************************************/


/*******************************************************************************
*                      LES FONCTIONS DE JUMP & LINK                           */
//
void jump_and_link(t_instruction *instruction, int32_t *registre, uint32_t *pc)
{
    registre[instruction->registre_destination] = *pc + 1;
    *pc = *pc + ((int32_t) instruction->immediat / 4);
}


//
void jump_and_link_register(
        t_instruction *instruction, int32_t *registre,
        uint32_t *pc)
{
    uint32_t tmp = *pc + 1;
    *pc = (registre[instruction->registre_source1] +
           ((int32_t) instruction->immediat) / 4);
    registre[instruction->registre_destination] = tmp;
}
/******************************************************************************/


/*******************************************************************************
*                      LES FONCTIONS DE RV32M                                 */

void multiply(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] *
            registre[instruction->registre_source2];
}

void multiply_high(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (int64_t) registre[instruction->registre_source1] *
            (int64_t) registre[instruction->registre_source2] >> 32u;
}

void
multiply_high_unsigned_signed(t_instruction *instruction, int32_t *registre)
{
    int32_t registre1 = (int32_t) registre[instruction->registre_source1];
    uint32_t registre2 = (uint32_t) registre[instruction->registre_source2];

    registre[instruction->registre_destination] =
            ((int64_t) registre1 *
             (int64_t) registre2) >> 32u;
}

void multiply_high_unsigned(t_instruction *instruction, int32_t *registre)
{
    uint32_t registre1 = (uint32_t) registre[instruction->registre_source1];
    uint32_t registre2 = (uint32_t) registre[instruction->registre_source2];

    registre[instruction->registre_destination] =
            ((int64_t) registre1 *
             (int64_t) registre2) >> 32u;
}

void divide(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] /
            registre[instruction->registre_source2];
}

void divide_unsigned(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (uint32_t) registre[instruction->registre_source1] /
            (uint32_t) registre[instruction->registre_source2];
}

void remainder_p(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            registre[instruction->registre_source1] %
            registre[instruction->registre_source2];
}

void remainder_unsigned(t_instruction *instruction, int32_t *registre)
{
    registre[instruction->registre_destination] =
            (uint32_t) registre[instruction->registre_source1] %
            (uint32_t) registre[instruction->registre_source2];
}

/*******************************************************************************
*                      LES FONCTIONS PRIVES                                   */

uint32_t set_bit(uint32_t value, uint8_t bitnum)
{
    uint32_t return_value = value;

    if (bitnum < 32)
    {
        return_value = value |= 1 << bitnum;
    }

    return return_value;
}