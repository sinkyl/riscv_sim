#include "unity/unity.h"
#include "stdio.h"
#include <string.h>
#include "stdlib.h"
#include <string.h>

#include "../include/processeur.h"


void test_la_creation_dune_struct_de_processeur_initialle()
{
    t_processeur *processeur = creer_processeur();

    TEST_ASSERT_NOT_NULL(processeur);
    TEST_ASSERT_EQUAL_INT(0, processeur->pc);

    free(processeur);
}


/*******************************************************************************
*                       TEST POUR LES LOADS
*******************************************************************************/
void test_load_byte_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rs1]);

    //la valeur que rd finalle qui se trouve dans la memoire[2 + 3]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = -55;
    TEST_ASSERT_EQUAL_INT32(201,
                            (int32_t) processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm]);

    load_byte(processeur->instructions, processeur->registres,
              processeur->memoire);

    TEST_ASSERT_EQUAL_HEX16(0xC9, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0x000000C9, processeur->registres[rd]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 0xC9, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_byte_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = -1;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rs1]);

    //la valeur que rd finalle qui se trouve dans la memoire[2 + 3]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = -55;
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[processeur->registres[rs1] +
                                                (int32_t) imm]);

    load_byte(processeur->instructions, processeur->registres,
              processeur->memoire);

    TEST_ASSERT_EQUAL_UINT32(201, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0x000000C9, processeur->registres[rd]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 201, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_half_word_avec_immediate_positif(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x5;
    int32_t imm = 0x4;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;

    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);

    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = -55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 1] = -55;

    //avec immediate positif
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[processeur->registres[rs1] +
                                                (int32_t) imm]);
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm + 1]);

    load_halfword(processeur->instructions, processeur->registres,
                  processeur->memoire);

    //donne 0x000000FF
    TEST_ASSERT_EQUAL_INT32(0xC9C9, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0x0000C9C9, processeur->registres[rd]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 0xC9C9, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_half_word_avec_immediate_negatif(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x5;
    int32_t imm = -1;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;

    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);

    //la valeur que rd finalle qui se trouve dans la memoire[1 + 4]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = -55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 1] = -55;

    //avec immediate positif
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[processeur->registres[rs1] +
                                                (int32_t) imm]);
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm + 1]);

    load_halfword(processeur->instructions, processeur->registres,
                  processeur->memoire);

    //donne 0x000000FF
    TEST_ASSERT_EQUAL_INT32(0xC9C9, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0x0000C9C9, processeur->registres[rd]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 0xC9C9, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_word_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x5;
    int32_t imm = 0x4;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    processeur->registres[rd] = 1234;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_UINT32(1234, processeur->registres[rd]);

    //la valeur que rd finalle qui se trouve dans la memoire[1 + 4]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = -55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 1] = -55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 2] = -55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 3] = -55;


    //avec immediate positif
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[processeur->registres[rs1] +
                                                (int32_t) imm]);
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm + 1]);
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm + 2]);
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm + 3]);

    load_word(processeur->instructions, processeur->registres,
              processeur->memoire);

    //donne 0xFFFFFFFF
    TEST_ASSERT_EQUAL_INT32(0xC9C9C900, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0xC9C9C900, processeur->registres[rd]);
    TEST_ASSERT_INT32_WITHIN(0xFFFFFFFF, 0xC9C9C900, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_word_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x5;
    int32_t imm = -1;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);;

    //la valeur que rd finalle qui se trouve dans la memoire[1 + 4]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = -55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 1] = -55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 2] = -55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 3] = -55;


    //avec immediate positif
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[processeur->registres[rs1] +
                                                (int32_t) imm]);
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm + 1]);
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm + 2]);
    TEST_ASSERT_EQUAL_INT32(201,
                            processeur->memoire[
                                    processeur->registres[rs1] +
                                    (int32_t) imm + 3]);

    load_word(processeur->instructions, processeur->registres,
              processeur->memoire);

    //donne 0xFFFFFFFF
    TEST_ASSERT_EQUAL_INT32(0xC9C9C900, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0xC9C9C900, processeur->registres[rd]);
    TEST_ASSERT_INT32_WITHIN(0xFFFFFFFF, 0xC9C9C900, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_byte_unsigned_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);

    //la valeur que rd finalle qui se trouve dans la memoire[2 + 3]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = 55;
    TEST_ASSERT_EQUAL_UINT32(55,
                             processeur->memoire[processeur->registres[rs1] +
                                                 (int32_t) imm]);

    load_byte(processeur->instructions, processeur->registres,
              processeur->memoire);

    TEST_ASSERT_EQUAL_UINT32(55, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0x00000037, processeur->registres[rd]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 55, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_shift_left_immediate(void)
{
//minimum de paramètres nécessaires
    uint32_t rd = 15;
    uint32_t rs1 = 1;
    uint32_t imm1 = 4;
    uint32_t imm2 = 8;
    uint32_t imm3 = 31;
    uint32_t imm4 = 0;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm1;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //tests
    //shift left de 4 bits
    processeur->registres[rs1] = 0xFFFFFFFF;
    shift_left_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFFFF0, processeur->registres[rd]);

    //shift left de 8 bits
    processeur->instructions->immediat = imm2;
    processeur->registres[rs1] = 0xFF00FFFF;
    shift_left_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x00FFFF00, processeur->registres[rd]);

    //shift left de 31 bits
    processeur->instructions->immediat = imm3;
    processeur->registres[rs1] = 0x8000000F;
    shift_left_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x80000000, processeur->registres[rd]);

    //shift left de 0 bits
    processeur->instructions->immediat = imm4;
    processeur->registres[rs1] = 0xF0F0F00F;
    shift_left_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xF0F0F00F, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_shift_right_immediate(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 12;
    uint32_t rs1 = 2;
    uint32_t imm1 = 4;
    uint32_t imm2 = 8;
    uint32_t imm3 = 31;
    uint32_t imm4 = 0;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm1;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //tests
    //shift right de 4 bits
    processeur->registres[rs1] = 0xFFFFFFFF;
    int32_t v = 0xFFFFFFFF;
    v = v >> 4;
    shift_right_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(0x0FFFFFFF, processeur->registres[rd]);

    //shift right de 8 bits
    processeur->instructions->immediat = imm2;
    processeur->registres[rs1] = 0xFFF00FFF;
    shift_right_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(0x00FFF00F, processeur->registres[rd]);

    //shift right de 31 bits
    processeur->instructions->immediat = imm3;
    processeur->registres[rs1] = 0xF000000F;
    shift_right_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(0x00000001, processeur->registres[rd]);

    //shift right de 0 bits
    processeur->instructions->immediat = imm4;
    processeur->registres[rs1] = 0xF0F0F00F;
    shift_right_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(0xF0F0F00F, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;

}


void test_shift_right_arith_immediate(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 14;
    uint32_t rs1 = 3;
    uint32_t imm1 = 4;
    uint32_t imm2 = 8;
    uint32_t imm3 = 31;
    uint32_t imm4 = 0;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm1;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //tests
    //shift right de 4 bits en gardant le sign original
    processeur->registres[rs1] = 0x00FFFFFF;
    shift_right_arith_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x000FFFFF, processeur->registres[rd]);

    //shift right de 8 bits en gardant le sign original
    processeur->instructions->immediat = imm2;
    processeur->registres[rs1] = 0x8FF00FFF;
    shift_right_arith_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xFF8FF00F, processeur->registres[rd]);

    //shift right de 31 bits en gardant le sign original
    processeur->instructions->immediat = imm3;
    processeur->registres[rs1] = 0x8000000F;
    shift_right_arith_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF, processeur->registres[rd]);

    //shift right de 0 bits en gardant le sign original
    processeur->instructions->immediat = imm4;
    processeur->registres[rs1] = 0xF0F0F00F;
    shift_right_arith_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xF0F0F00F, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_shift_left(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 14;
    uint32_t rs1 = 3;
    uint32_t rs2 = 4;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //tests
    //shift left de 4 bits
    processeur->registres[rs1] = 0x00FFFFFF;
    processeur->registres[rs2] = 4;
    shift_left(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x0FFFFFF0, processeur->registres[rd]);

    //shift left de 8 bits
    processeur->registres[rs1] = 0x8FF00FFF;
    processeur->registres[rs2] = 8;
    shift_left(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xF00FFF00, processeur->registres[rd]);

    //shift left de 31 bits
    processeur->registres[rs1] = 0x8000000F;
    processeur->registres[rs2] = 31;
    shift_left(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x80000000, processeur->registres[rd]);

    //shift left de 0 bits
    processeur->registres[rs1] = 0xF0F0F00F;
    processeur->registres[rs2] = 0;
    shift_left(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xF0F0F00F, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;

}


void test_shift_right(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 15;
    uint32_t rs1 = 4;
    uint32_t rs2 = 5;


    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //tests
    //shift right de 4 bits
    processeur->registres[rs1] = 0x0FFFFFFF;
    processeur->registres[rs2] = 4;
    shift_right(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x00FFFFFF, processeur->registres[rd]);

    //shift right de 8 bits
    processeur->registres[rs1] = 0x8FF00FFF;
    processeur->registres[rs2] = 8;
    shift_right(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x008FF00F, processeur->registres[rd]);

    //shift right de 31 bits
    processeur->registres[rs1] = 0x8000000F;
    processeur->registres[rs2] = 31;
    shift_right(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x00000001, processeur->registres[rd]);

    //shift right de 0 bits
    processeur->registres[rs1] = 0xF0F0F00F;
    processeur->registres[rs2] = 0;
    shift_right(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xF0F0F00F, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_shift_right_arith(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 12;
    uint32_t rs1 = 6;
    uint32_t rs2 = 7;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //tests
    //shift right de 4 bits en gardant le bit de sign original
    processeur->registres[rs1] = 0x0FFFFFFF;
    processeur->registres[rs2] = 4;
    shift_right_arith(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x00FFFFFF, processeur->registres[rd]);

    //shift right de 8 bits
    processeur->registres[rs1] = 0x8FF00FFF;
    processeur->registres[rs2] = 8;
    shift_right_arith(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xFF8FF00F, processeur->registres[rd]);

    //shift right de 31 bits
    processeur->registres[rs1] = 0x1000000F;
    processeur->registres[rs2] = 31;
    shift_right_arith(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0x0, processeur->registres[rd]);

    //shift right de 0 bits
    processeur->registres[rs1] = 0xF0F0F00F;
    processeur->registres[rs2] = 0;
    shift_right_arith(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_UINT32(0xF0F0F00F, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;

}


void test_addition(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 12;
    uint32_t rs1 = 6;
    uint32_t rs2 = 7;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //add rs1 neg rs2 pos
    processeur->registres[rs1] = -1;
    processeur->registres[rs2] = 3;
    addition(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(2, processeur->registres[rd]);

    //add rs1 pos rs2 neg
    processeur->registres[rs1] = 1000;
    processeur->registres[rs2] = -50;
    addition(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(950, processeur->registres[rd]);

    //add rs1 neg rs2 neg
    processeur->registres[rs1] = -51;
    processeur->registres[rs2] = -50;
    addition(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(-101, processeur->registres[rd]);

    //add rs1 pos rs2 pos
    processeur->registres[rs1] = 500;
    processeur->registres[rs2] = 40;
    addition(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(540, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_addition_immediate(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 12;
    uint32_t rs1 = 6;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //add rs1 neg imm pos
    processeur->registres[rs1] = -1;
    processeur->instructions->immediat = 1000;
    addition_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(999, processeur->registres[rd]);

    //add rs1 pos imm neg
    processeur->registres[rs1] = 1000;
    processeur->instructions->immediat = -1;
    addition_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(999, processeur->registres[rd]);

    //add rs1 neg imm neg
    processeur->registres[rs1] = -50;
    processeur->instructions->immediat = 4000;
    addition_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(3950, processeur->registres[rd]);

    //add rs1 pos imm pos
    processeur->registres[rs1] = 500;
    processeur->instructions->immediat = 4095;
    addition_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(4595, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_subtract(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 12;
    uint32_t rs1 = 6;
    uint32_t rs2 = 7;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //sub rs1 neg rs2 pos
    processeur->registres[rs1] = -1;
    processeur->registres[rs2] = 3;
    subtract(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(-4, processeur->registres[rd]);

    //sub rs1 pos rs2 neg
    processeur->registres[rs1] = 1000;
    processeur->registres[rs2] = -50;
    subtract(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(1050, processeur->registres[rd]);

    //sub rs1 neg rs2 neg
    processeur->registres[rs1] = -51;
    processeur->registres[rs2] = -50;
    subtract(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(-1, processeur->registres[rd]);

    //sub rs1 pos rs2 pos
    processeur->registres[rs1] = 500;
    processeur->registres[rs2] = 40;
    subtract(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(460, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_upper_immediate(void)
{
    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(3*sizeof(t_instruction));

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //test lui
    strcpy(instruction->code_hexa, "00064137");
    strcpy(instruction->code_hexa, "007d0237");
    strcpy(instruction->code_hexa, "00bb82b7");
    decode_tableau_instructions(instruction, 3);

    load_upper_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(100 << 12,
                            processeur->registres[instruction->registre_destination]);

    load_upper_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(2000 << 12,
                            processeur->registres[instruction->registre_destination]);

    load_upper_immediate(instruction, processeur->registres);
    TEST_ASSERT_EQUAL_INT32(3000 << 12,
                            processeur->registres[instruction->registre_destination]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_add_upper_imm_to_pc(void)
{
    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(2*sizeof(t_instruction));

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    strcpy(instruction->code_hexa, "00000197");
    strcpy(instruction->code_hexa, "00064317");
    decode_tableau_instructions(instruction, 2);

    uint32_t pc = 1000; //adresse arbitraire pc
    add_upper_imm_to_pc(instruction, processeur->registres, &pc);
    TEST_ASSERT_EQUAL_INT32(pc,
                            processeur->registres[instruction->registre_destination]);


    pc = 2000;
    add_upper_imm_to_pc(instruction, processeur->registres, &pc);
    TEST_ASSERT_EQUAL_INT32(pc + instruction->immediat,
                            processeur->registres[instruction->registre_destination]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_jump_and_link(void)
{
    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(2 * sizeof(t_instruction));

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //decode instruction jal 24 et jal -20 respectivement
    strcpy(instruction[0].code_hexa, "018000ef");
    strcpy(instruction[1].code_hexa, "fedff0ef");
    decode_tableau_instructions(instruction, 2);

    uint32_t pc = 12; //adresse arbitraire
    uint32_t temp_pc = pc;
    jump_and_link(&instruction[0], processeur->registres, &pc);
    TEST_ASSERT_EQUAL_INT32(temp_pc + 4,
                            processeur->registres[instruction->registre_destination]);
    TEST_ASSERT_EQUAL_INT32(pc, temp_pc + instruction[0].immediat);

    pc = 24;
    temp_pc = pc;
    jump_and_link(&instruction[1], processeur->registres, &pc);
    TEST_ASSERT_EQUAL_INT32(temp_pc + 4,
                            processeur->registres[instruction->registre_destination]);
    TEST_ASSERT_EQUAL_INT32(pc, temp_pc + instruction[1].immediat);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_jump_and_link_register(void)
{
    //minimum de paramètres nécessaires
    uint32_t rd = 12;
    uint32_t rs1 = 6;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    //jalr 24 et jal -20 respectivement
    instruction->immediat = 24;
    processeur->registres[rs1] = 40;
    uint32_t pc = 1000;
    uint32_t temp_pc = pc;
    jump_and_link_register(instruction, processeur->registres, &pc);
    TEST_ASSERT_EQUAL_INT32(temp_pc + 4,
                            processeur->registres[instruction->registre_destination]);
    TEST_ASSERT_EQUAL_INT32(pc, temp_pc + 40 + 24);

    instruction->immediat = -30;
    processeur->registres[rs1] = -11;
    pc = 1000;
    temp_pc = pc;
    jump_and_link_register(instruction, processeur->registres, &pc);
    TEST_ASSERT_EQUAL_INT32(temp_pc + 4,
                            processeur->registres[instruction->registre_destination]);
    TEST_ASSERT_EQUAL_INT32(pc, temp_pc + (-30 - 11) - 1);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_byte_unsigned_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = -1;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);

    //la valeur que rd finalle qui se trouve dans la memoire[2 + 3]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = 55;
    TEST_ASSERT_EQUAL_UINT32(55,
                             processeur->memoire[processeur->registres[rs1] +
                                                 (int32_t) imm]);

    load_byte_unsigned(processeur->instructions, processeur->registres,
                       processeur->memoire);

    TEST_ASSERT_EQUAL_UINT32(55, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0x00000037, processeur->registres[rd]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 55, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_word_unsigned_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x5;
    int32_t imm = 0x4;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);

    //la valeur que rd finalle qui se trouve dans la memoire[1 + 4]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = 55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 1] = 55;

    //avec immediate positif
    TEST_ASSERT_EQUAL_UINT32(55,
                             processeur->memoire[processeur->registres[rs1] +
                                                 (int32_t) imm]);
    TEST_ASSERT_EQUAL_UINT32(55,
                             processeur->memoire[
                                     processeur->registres[rs1] +
                                     (int32_t) imm + 1]);

    load_halfword_unsigned(processeur->instructions, processeur->registres,
                           processeur->memoire);

    TEST_ASSERT_EQUAL_UINT32(0x3737, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0x00003737, processeur->registres[rd]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 0x3737, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_load_word_unsigned_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x5;
    int32_t imm = -1;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);

    //la valeur que rd finalle qui se trouve dans la memoire[1 + 4]
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm] = 55;
    processeur->memoire[processeur->registres[rs1] + (int32_t) imm + 1] = 55;

    //avec immediate positif
    TEST_ASSERT_EQUAL_UINT32(55,
                             processeur->memoire[processeur->registres[rs1] +
                                                 (int32_t) imm]);
    TEST_ASSERT_EQUAL_UINT32(55,
                             processeur->memoire[
                                     processeur->registres[rs1] +
                                     (int32_t) imm + 1]);

    load_halfword_unsigned(processeur->instructions, processeur->registres,
                           processeur->memoire);

    TEST_ASSERT_EQUAL_UINT32(0x3737, processeur->registres[rd]);
    TEST_ASSERT_BITS(0xFFFFFFFF, 0x00003737, processeur->registres[rd]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 0x3737, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


/*******************************************************************************
*                       TEST POUR LES STORES
*******************************************************************************/
void test_store_byte_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x1;
    uint32_t rs2 = 0x2;
    int32_t imm = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    processeur->registres[rs2] = 2;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_UINT32(2, processeur->registres[rs2]);

    processeur->registres[instruction->registre_source2] = -70;
    TEST_ASSERT_EQUAL_INT32(-70,
                            processeur->registres[instruction->registre_source2]);

    store_byte(processeur->instructions, processeur->registres,
               processeur->memoire);

    TEST_ASSERT_EQUAL_HEX16(0xBA,
                            processeur->memoire[instruction->registre_source1 +
                                                (int32_t) instruction->immediat]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 0xBA,
                            processeur->memoire[instruction->registre_source1 +
                                                (int32_t) instruction->immediat]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_store_byte_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x1;
    uint32_t rs2 = 0x2;
    int32_t imm = -1;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    processeur->registres[rs2] = 2;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_UINT32(2, processeur->registres[rs2]);

    processeur->registres[instruction->registre_source2] = -70;
    TEST_ASSERT_EQUAL_INT32(-70,
                            processeur->registres[instruction->registre_source2]);

    store_byte(processeur->instructions, processeur->registres,
               processeur->memoire);

    TEST_ASSERT_EQUAL_HEX16(0xBA,
                            processeur->memoire[instruction->registre_source1 +
                                                (int32_t) instruction->immediat]);
    TEST_ASSERT_INT8_WITHIN(0xFF, 0xBA,
                            processeur->memoire[instruction->registre_source1 +
                                                (int32_t) instruction->immediat]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_store_half_word_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x1;
    uint32_t rs2 = 0x2;
    int32_t imm = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    processeur->registres[rs2] = 2;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_UINT32(2, processeur->registres[rs2]);

    processeur->registres[instruction->registre_source2] = 25432;
    TEST_ASSERT_EQUAL_INT32(25432,
                            processeur->registres[instruction->registre_source2]);
    TEST_ASSERT_BITS(0xFFFF, 0x6358,
                     processeur->registres[instruction->registre_source2]);

    store_half_word(processeur->instructions, processeur->registres,
                    processeur->memoire);

    TEST_ASSERT_EQUAL_HEX16(88,
                            processeur->memoire[instruction->registre_source1 +
                                                (int32_t) instruction->immediat]);
    TEST_ASSERT_EQUAL_HEX16(99,
                            processeur->memoire[instruction->registre_source1 +
                                                (int32_t) instruction->immediat +
                                                1]);

    TEST_ASSERT_INT16_WITHIN(0xFFFF, 0x6358,
                             processeur->memoire[instruction->registre_source2 +
                                                 instruction->immediat]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_store_half_word_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x1;
    uint32_t rs2 = 0x2;
    int32_t imm = -1;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 1;
    processeur->registres[rs2] = 2;
    TEST_ASSERT_EQUAL_UINT32(1, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_UINT32(2, processeur->registres[rs2]);

    processeur->registres[instruction->registre_source2] = 25432;
    TEST_ASSERT_EQUAL_INT32(25432,
                            processeur->registres[instruction->registre_source2]);
    TEST_ASSERT_BITS(0xFFFF, 0x6358,
                     processeur->registres[instruction->registre_source2]);

    store_half_word(processeur->instructions, processeur->registres,
                    processeur->memoire);

    TEST_ASSERT_EQUAL_HEX8(88,
                           processeur->memoire[instruction->registre_source1 +
                                               (int32_t) instruction->immediat]);
    TEST_ASSERT_EQUAL_HEX8(99,
                           processeur->memoire[instruction->registre_source1 +
                                               (int32_t) instruction->immediat +
                                               1]);

    TEST_ASSERT_INT16_WITHIN(0xFFFF, 0x6358,
                             processeur->memoire[instruction->registre_source2 +
                                                 instruction->immediat]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_store_word_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x1;
    uint32_t rs2 = 0x2;
    int32_t imm = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    processeur->registres[instruction->registre_source1] = 0;
    processeur->registres[instruction->registre_source2] = 0x7FFFFFFF;

    TEST_ASSERT_EQUAL_INT32(2147483647,
                            processeur->registres[instruction->registre_source2]);

    store_word(processeur->instructions, processeur->registres,
               processeur->memoire);

    TEST_ASSERT_EQUAL_HEX8(0xFF,
                           processeur->memoire[processeur->registres[instruction->registre_source1] +
                                               (int32_t) instruction->immediat]);
    TEST_ASSERT_EQUAL_HEX16(0xFF,
                            processeur->memoire[processeur->registres[instruction->registre_source1] +
                                                (int32_t) instruction->immediat +
                                                1]);
    TEST_ASSERT_EQUAL_HEX16(0xFF,
                            processeur->memoire[processeur->registres[instruction->registre_source1] +
                                                (int32_t) instruction->immediat +
                                                2]);
    TEST_ASSERT_EQUAL_HEX16(0x7F,
                            processeur->memoire[processeur->registres[instruction->registre_source1] +
                                                (int32_t) instruction->immediat +
                                                3]);
    TEST_ASSERT_INT16_WITHIN(0xFFFFFFFF, 0x7FFFFFFF,
                             processeur->memoire[processeur->registres[instruction->registre_source1] +
                                                 (int32_t) instruction->immediat]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_store_word_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x1;
    uint32_t rs2 = 0x2;
    int32_t imm = -1;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    processeur->registres[instruction->registre_source1] = 100;
    processeur->registres[instruction->registre_source2] = 0x7FFFFFFF;


    TEST_ASSERT_EQUAL_INT32(2147483647,
                            processeur->registres[instruction->registre_source2]);

    store_word(processeur->instructions, processeur->registres,
               processeur->memoire);

    TEST_ASSERT_EQUAL_HEX8(0xFF,
                           processeur->memoire[processeur->registres[instruction->registre_source1] +
                                               (int32_t) instruction->immediat]);
    TEST_ASSERT_EQUAL_HEX16(0xFF,
                            processeur->memoire[processeur->registres[instruction->registre_source1] +
                                                (int32_t) instruction->immediat +
                                                1]);
    TEST_ASSERT_EQUAL_HEX16(0xFF,
                            processeur->memoire[processeur->registres[instruction->registre_source1] +
                                                (int32_t) instruction->immediat +
                                                2]);
    TEST_ASSERT_EQUAL_HEX16(0x7F,
                            processeur->memoire[processeur->registres[instruction->registre_source1] +
                                                (int32_t) instruction->immediat +
                                                3]);
    TEST_ASSERT_INT16_WITHIN(0xFFFFFFFF, 0x7FFFFFFF,
                             processeur->memoire[processeur->registres[instruction->registre_source1] +
                                                 (int32_t) instruction->immediat]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


/*******************************************************************************
*                       TEST POUR LES LOGIQUES
*******************************************************************************/
void test_xor()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rs2] = 0x42A8CBF2;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(0x42A8CBF2, processeur->registres[rs2]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    xor(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0x113067DD, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_xor_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = 0xABC;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    xor_immediate(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0x5398A693, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_xor_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = -123456;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    xor_immediate(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0xAC66B1EF, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_or()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rs2] = 0x42A8CBF2;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(0x42A8CBF2, processeur->registres[rs2]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    or(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0x53B8EFFF, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_or_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = 0xABC;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    or_immediate(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0x5398AEBF, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_or_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = -123456;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    or_immediate(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0xFFFEBDEF, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_and()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rs2] = 0x42A8CBF2;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(0x42A8CBF2, processeur->registres[rs2]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    and(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0x42888822, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_and_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = 0xABC;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    and_immediate(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0x82C, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_and_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = -123456;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = 0x5398AC2F;
    processeur->registres[rd] = 1;
    TEST_ASSERT_EQUAL_INT32(0x5398AC2F, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    and_immediate(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0x53980C00, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


/*******************************************************************************
*                       TEST POUR LES COMPARAISONS
*******************************************************************************/
void test_set()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = -9999999;
    processeur->registres[rs2] = -7777777;
    TEST_ASSERT_EQUAL_INT32(-9999999, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(-7777777, processeur->registres[rs2]);

    set(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_set_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = -7777777;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = -9999999;

    TEST_ASSERT_EQUAL_INT32(-9999999, processeur->registres[rs1]);

    set_immediate(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_set_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = 7777777;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = -9999999;

    TEST_ASSERT_EQUAL_INT32(-9999999, processeur->registres[rs1]);

    set_immediate(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_set_usigned()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x3;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = -9999999;
    processeur->registres[rs2] = -7777777;
    TEST_ASSERT_EQUAL_INT32(-9999999, processeur->registres[rs1]);
    TEST_ASSERT_EQUAL_INT32(-7777777, processeur->registres[rs2]);

    set_unsigned(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_set_unsigned_avec_immediate_positif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = -7777777;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = -9999999;

    TEST_ASSERT_EQUAL_INT32(-9999999, processeur->registres[rs1]);

    set_immediate_unsigned(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(1, processeur->registres[rd]);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_set_unsigned_avec_immediate_negatif()
{
    //minimum de paramètres nécessaires
    uint32_t rd = 0x1;
    uint32_t rs1 = 0x2;
    int32_t imm = 7777777;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->immediat = imm;
    instruction->registre_source1 = rs1;
    instruction->registre_destination = rd;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;

    processeur->registres[rs1] = -9999999;

    TEST_ASSERT_EQUAL_INT32(-9999999, processeur->registres[rs1]);

    set_immediate_unsigned(processeur->instructions, processeur->registres);

    TEST_ASSERT_EQUAL_INT32(0, processeur->registres[rd]);
    // NON CAR SIGNÉ

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


/*******************************************************************************
*                       TEST POUR LES BRANCHES
*******************************************************************************/
void test_branch_equal()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x2;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_equal(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + (uint32_t)imm, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_equal_sinon_pc_plus_4()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x1;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_equal(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + 4, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_not_equal()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x3;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_not_equal(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + imm, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_not_equal_sinon_pc_plus_4()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = 0x2;
    uint32_t rs2 = 0x2;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_not_equal(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + 4, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_less_than()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = -0x3;
    uint32_t rs2 = -0x2;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_less_than(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + imm, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_less_than_sinon_pc_plus_4()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = -0x2;
    uint32_t rs2 = -0x3;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_less_than(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + 4, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_greater_or_equal()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = -0x1;
    uint32_t rs2 = -0x3;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_greater_or_equal(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + imm, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_greater_or_equal_sinon_pc_plus_4()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = -0x3;
    uint32_t rs2 = -0x2;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_greater_or_equal(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + 4, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_less_than_unsigned()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = -0x3;
    uint32_t rs2 = -0x2;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_less_unsigned(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + imm, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_less_than_unsigned_sinon_pc_plus_4()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = -0x2;
    uint32_t rs2 = -0x3;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_less_unsigned(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + 4, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_greater_or_equal_unsigned()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = -0x1;
    uint32_t rs2 = -0x3;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_greater_or_equal_unsigned(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + imm, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}


void test_branch_greater_or_equal_unsigned_sinon_pc_plus_4()
{
    //minimum de paramètres nécessaires
    uint32_t rs1 = -0x3;
    uint32_t rs2 = -0x2;
    int32_t imm = -10;

    //construit UNE instruction
    t_instruction *instruction;
    instruction = (t_instruction *) malloc(sizeof(t_instruction));

    instruction->registre_source1 = rs1;
    instruction->registre_source2 = rs2;
    instruction->immediat = imm;

    //construit le processeur
    t_processeur *processeur;
    processeur = creer_processeur();
    processeur->instructions = instruction;
    //pc déjà initialisé à 0 lors de l'initialisation du processeur
    //mais on va le mettre dans le style addresse
    processeur->pc = 0x12345678;

    branch_greater_or_equal_unsigned(processeur->instructions, processeur->registres, &processeur->pc);

    //pc doit avoir eun -10 sur sa valeur
    TEST_ASSERT_EQUAL_INT32(0x12345678 + 4, processeur->pc);

    free(instruction);
    free(processeur);
    instruction = NULL;
    processeur = NULL;
}