#include "unity/unity.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#include "../include/decodeur.h"


void test_assemblage_instructions()
{
    t_instruction_bloc *instruction_bloc;
            
    instruction_bloc = assemblage_instructions("../input/riscv_test_small.txt");

    UnityAssertEqualString("10000517",
                           instruction_bloc->instructions[0].code_hexa,
                           instruction_bloc->instructions[0].code_hexa, 1);
    UnityAssertEqualString("00052503",
                           instruction_bloc->instructions[1].code_hexa,
                           instruction_bloc->instructions[1].code_hexa, 2);
    UnityAssertEqualString("01c000ef",
                           instruction_bloc->instructions[2].code_hexa,
                           instruction_bloc->instructions[2].code_hexa, 3);
    UnityAssertEqualString("00050593",
                           instruction_bloc->instructions[3].code_hexa,
                           instruction_bloc->instructions[3].code_hexa, 4);
    free(instruction_bloc);
    instruction_bloc = NULL;
}


void test_decodage_instruction(void)
{
    t_instruction_bloc *instruction_bloc = assemblage_instructions(
            "../input/riscv_test_small2.txt");

    decode_tableau_instructions(instruction_bloc->instructions, instruction_bloc->nb_instructions);

    printf("test instruction 0\n");
    TEST_ASSERT_EQUAL_INT(U, instruction_bloc->instructions[0].format);
    UnityAssertEqualString("LUI", instruction_bloc->instructions[0].nom, "0",
                           0);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[0].registre_destination);
    TEST_ASSERT_EQUAL_INT(100 << 12,
                          instruction_bloc->instructions[0].immediat);

    printf("test instruction 1\n");
    TEST_ASSERT_EQUAL_INT(U, instruction_bloc->instructions[1].format);
    UnityAssertEqualString("AUIPC", instruction_bloc->instructions[1].nom,
                           "1", 1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[1].registre_destination);
    TEST_ASSERT_EQUAL_INT(0x1024 << 12,
                          instruction_bloc->instructions[1].immediat);

    printf("test instruction 2\n");
    TEST_ASSERT_EQUAL_INT(J, instruction_bloc->instructions[2].format);
    UnityAssertEqualString("JAL", instruction_bloc->instructions[2].nom, "2",
                           2);
    TEST_ASSERT_EQUAL_INT(4,
                          instruction_bloc->instructions[2].registre_destination);
    TEST_ASSERT_EQUAL_INT(4, instruction_bloc->instructions[2].immediat);

    printf("test instruction 3\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[3].format);
    UnityAssertEqualString("JALR", instruction_bloc->instructions[3].nom, "3",
                           3);
    TEST_ASSERT_EQUAL_INT(0,
                          instruction_bloc->instructions[3].registre_destination);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[3].registre_source1);
    TEST_ASSERT_EQUAL_INT(0, instruction_bloc->instructions[3].immediat);

    printf("test instruction 4\n");
    TEST_ASSERT_EQUAL_INT(B, instruction_bloc->instructions[4].format);
    UnityAssertEqualString("BEQ", instruction_bloc->instructions[4].nom, "4",
                           4);
    TEST_ASSERT_EQUAL_INT(0,
                          instruction_bloc->instructions[4].registre_source1);
    TEST_ASSERT_EQUAL_INT(0,
                          instruction_bloc->instructions[4].registre_source2);
    TEST_ASSERT_EQUAL_INT(24, instruction_bloc->instructions[4].immediat);

    printf("test instruction 5\n");
    TEST_ASSERT_EQUAL_INT(B, instruction_bloc->instructions[5].format);
    UnityAssertEqualString("BNE", instruction_bloc->instructions[5].nom, "5",
                           5);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[5].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[5].registre_source2);
    TEST_ASSERT_EQUAL_INT(20, instruction_bloc->instructions[5].immediat);

    printf("test instruction 6\n");
    TEST_ASSERT_EQUAL_INT(B, instruction_bloc->instructions[6].format);
    UnityAssertEqualString("BLT", instruction_bloc->instructions[6].nom, "6",
                           6);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[6].registre_source1);
    TEST_ASSERT_EQUAL_INT(4,
                          instruction_bloc->instructions[6].registre_source2);
    TEST_ASSERT_EQUAL_INT(16, instruction_bloc->instructions[6].immediat);

    printf("test instruction 7\n");
    TEST_ASSERT_EQUAL_INT(B, instruction_bloc->instructions[7].format);
    UnityAssertEqualString("BGE", instruction_bloc->instructions[7].nom, "7",
                           7);
    TEST_ASSERT_EQUAL_INT(12,
                          instruction_bloc->instructions[7].registre_source1);
    TEST_ASSERT_EQUAL_INT(13,
                          instruction_bloc->instructions[7].registre_source2);
    TEST_ASSERT_EQUAL_INT(12, instruction_bloc->instructions[7].immediat);

    printf("test instruction 8\n");
    TEST_ASSERT_EQUAL_INT(B, instruction_bloc->instructions[8].format);
    UnityAssertEqualString("BLTU", instruction_bloc->instructions[8].nom, "8",
                           8);
    TEST_ASSERT_EQUAL_INT(11,
                          instruction_bloc->instructions[8].registre_source1);
    TEST_ASSERT_EQUAL_INT(4,
                          instruction_bloc->instructions[8].registre_source2);
    TEST_ASSERT_EQUAL_INT(8, instruction_bloc->instructions[8].immediat);

    printf("test instruction 9\n");
    TEST_ASSERT_EQUAL_INT(B, instruction_bloc->instructions[9].format);
    UnityAssertEqualString("BGEU", instruction_bloc->instructions[9].nom, "9",
                           9);
    TEST_ASSERT_EQUAL_INT(13,
                          instruction_bloc->instructions[9].registre_source1);
    TEST_ASSERT_EQUAL_INT(12,
                          instruction_bloc->instructions[9].registre_source2);
    TEST_ASSERT_EQUAL_INT(4, instruction_bloc->instructions[9].immediat);

    printf("test instruction 10\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[10].format);
    UnityAssertEqualString("LB", instruction_bloc->instructions[10].nom, "10",
                           10);
    TEST_ASSERT_EQUAL_INT(5,
                          instruction_bloc->instructions[10].registre_destination);
    TEST_ASSERT_EQUAL_INT(11,
                          instruction_bloc->instructions[10].registre_source1);
    TEST_ASSERT_EQUAL_INT(0, instruction_bloc->instructions[10].immediat);

    printf("test instruction 11\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[11].format);
    UnityAssertEqualString("LH", instruction_bloc->instructions[11].nom, "11",
                           11);
    TEST_ASSERT_EQUAL_INT(5,
                          instruction_bloc->instructions[11].registre_destination);
    TEST_ASSERT_EQUAL_INT(12,
                          instruction_bloc->instructions[11].registre_source1);
    TEST_ASSERT_EQUAL_INT(100, instruction_bloc->instructions[11].immediat);

    printf("test instruction 12\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[12].format);
    UnityAssertEqualString("LW", instruction_bloc->instructions[12].nom, "12",
                           12);
    TEST_ASSERT_EQUAL_INT(5,
                          instruction_bloc->instructions[12].registre_destination);
    TEST_ASSERT_EQUAL_INT(13,
                          instruction_bloc->instructions[12].registre_source1);
    TEST_ASSERT_EQUAL_INT(450, instruction_bloc->instructions[12].immediat);

    printf("test instruction 13\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[13].format);
    UnityAssertEqualString("LBU", instruction_bloc->instructions[13].nom,
                           "13", 13);
    TEST_ASSERT_EQUAL_INT(5,
                          instruction_bloc->instructions[13].registre_destination);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[13].registre_source1);
    TEST_ASSERT_EQUAL_INT(250, instruction_bloc->instructions[13].immediat);

    printf("test instruction 14\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[14].format);
    UnityAssertEqualString("LHU", instruction_bloc->instructions[14].nom,
                           "14", 14);
    TEST_ASSERT_EQUAL_INT(5,
                          instruction_bloc->instructions[14].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[14].registre_source1);
    TEST_ASSERT_EQUAL_INT(-12u, instruction_bloc->instructions[14].immediat);

    printf("test instruction 16\n");
    TEST_ASSERT_EQUAL_INT(S, instruction_bloc->instructions[16].format);
    UnityAssertEqualString("SB", instruction_bloc->instructions[16].nom, "16",
                           16);
    TEST_ASSERT_EQUAL_INT(10,
                          instruction_bloc->instructions[16].registre_source1);
    TEST_ASSERT_EQUAL_INT(12,
                          instruction_bloc->instructions[16].registre_source2);
    TEST_ASSERT_EQUAL_INT(136, instruction_bloc->instructions[16].immediat);

    printf("test instruction 18\n");
    TEST_ASSERT_EQUAL_INT(S, instruction_bloc->instructions[18].format);
    UnityAssertEqualString("SH", instruction_bloc->instructions[18].nom, "18",
                           18);
    TEST_ASSERT_EQUAL_INT(10,
                          instruction_bloc->instructions[18].registre_source1);
    TEST_ASSERT_EQUAL_INT(13,
                          instruction_bloc->instructions[18].registre_source2);
    TEST_ASSERT_EQUAL_INT(128, instruction_bloc->instructions[18].immediat);

    printf("test instruction 20\n");
    TEST_ASSERT_EQUAL_INT(S, instruction_bloc->instructions[20].format);
    UnityAssertEqualString("SW", instruction_bloc->instructions[20].nom, "20",
                           20);
    TEST_ASSERT_EQUAL_INT(10,
                          instruction_bloc->instructions[20].registre_source1);
    TEST_ASSERT_EQUAL_INT(14,
                          instruction_bloc->instructions[20].registre_source2);
    TEST_ASSERT_EQUAL_INT(120, instruction_bloc->instructions[20].immediat);

    printf("test instruction 21\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[21].format);
    UnityAssertEqualString("ADDI", instruction_bloc->instructions[21].nom,
                           "21", 21);
    TEST_ASSERT_EQUAL_INT(10,
                          instruction_bloc->instructions[21].registre_destination);
    TEST_ASSERT_EQUAL_INT(10,
                          instruction_bloc->instructions[21].registre_source1);
    TEST_ASSERT_EQUAL_INT(1, instruction_bloc->instructions[21].immediat);

    printf("test instruction 22\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[22].format);
    UnityAssertEqualString("SLTI", instruction_bloc->instructions[22].nom,
                           "22", 22);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[22].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[22].registre_source1);
    TEST_ASSERT_EQUAL_INT(100, instruction_bloc->instructions[22].immediat);

    printf("test instruction 23\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[23].format);
    UnityAssertEqualString("SLTIU", instruction_bloc->instructions[23].nom,
                           "23", 23);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[23].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[23].registre_source1);
    TEST_ASSERT_EQUAL_INT(250, instruction_bloc->instructions[23].immediat);

    printf("test instruction 24\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[24].format);
    UnityAssertEqualString("XORI", instruction_bloc->instructions[24].nom,
                           "24", 24);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[24].registre_destination);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[24].registre_source1);
    TEST_ASSERT_EQUAL_INT(1111, instruction_bloc->instructions[24].immediat);

    printf("test instruction 25\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[25].format);
    UnityAssertEqualString("ORI", instruction_bloc->instructions[25].nom,
                           "25", 25);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[25].registre_destination);
    TEST_ASSERT_EQUAL_INT(5,
                          instruction_bloc->instructions[25].registre_source1);
    TEST_ASSERT_EQUAL_INT(1010, instruction_bloc->instructions[25].immediat);

    printf("test instruction 26\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[26].format);
    UnityAssertEqualString("ANDI", instruction_bloc->instructions[26].nom,
                           "26", 26);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[26].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[26].registre_source1);
    TEST_ASSERT_EQUAL_INT(1010, instruction_bloc->instructions[26].immediat);

    printf("test instruction 27\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[27].format);
    UnityAssertEqualString("SLLI", instruction_bloc->instructions[27].nom,
                           "27", 27);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[27].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[27].registre_source1);
    TEST_ASSERT_EQUAL_INT(3, instruction_bloc->instructions[27].immediat);

    printf("test instruction 28\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[28].format);
    UnityAssertEqualString("SRLI", instruction_bloc->instructions[28].nom,
                           "28", 28);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[28].registre_destination);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[28].registre_source1);
    TEST_ASSERT_EQUAL_INT(6, instruction_bloc->instructions[28].immediat);

    printf("test instruction 29\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[29].format);
    UnityAssertEqualString("SRAI", instruction_bloc->instructions[29].nom,
                           "29", 29);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[29].registre_destination);
    TEST_ASSERT_EQUAL_INT(9,
                          instruction_bloc->instructions[29].registre_source1);
    TEST_ASSERT_EQUAL_INT(1034, instruction_bloc->instructions[29].immediat);
    // 1034 a cause que le shift a gauche est encoder dans la partie haute du immediat

    printf("test instruction 30\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[30].format);
    UnityAssertEqualString("ADD", instruction_bloc->instructions[30].nom,
                           "30", 30);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[30].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[30].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[30].registre_source2);

    printf("test instruction 31\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[31].format);
    UnityAssertEqualString("SUB", instruction_bloc->instructions[31].nom,
                           "31", 31);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[31].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[31].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[31].registre_source2);

    printf("test instruction 32\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[32].format);
    UnityAssertEqualString("SLL", instruction_bloc->instructions[32].nom,
                           "32", 32);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[32].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[32].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[32].registre_source2);

    printf("test instruction 33\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[33].format);
    UnityAssertEqualString("SLT", instruction_bloc->instructions[33].nom,
                           "33", 33);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[33].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[33].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[33].registre_source2);

    printf("test instruction 34\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[34].format);
    UnityAssertEqualString("SLTU", instruction_bloc->instructions[34].nom,
                           "34", 34);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[34].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[34].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[34].registre_source2);

    printf("test instruction 35\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[35].format);
    UnityAssertEqualString("XOR", instruction_bloc->instructions[35].nom,
                           "35", 35);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[35].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[35].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[35].registre_source2);

    printf("test instruction 36\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[36].format);
    UnityAssertEqualString("SRL", instruction_bloc->instructions[36].nom,
                           "36", 36);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[36].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[36].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[36].registre_source2);

    printf("test instruction 37\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[37].format);
    UnityAssertEqualString("SRA", instruction_bloc->instructions[37].nom,
                           "37", 37);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[37].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[37].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[37].registre_source2);

    printf("test instruction 38\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[38].format);
    UnityAssertEqualString("OR", instruction_bloc->instructions[38].nom, "38",
                           38);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[38].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[38].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[38].registre_source2);

    printf("test instruction 39\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[39].format);
    UnityAssertEqualString("AND", instruction_bloc->instructions[39].nom,
                           "39", 39);
    TEST_ASSERT_EQUAL_INT(1,
                          instruction_bloc->instructions[39].registre_destination);
    TEST_ASSERT_EQUAL_INT(2,
                          instruction_bloc->instructions[39].registre_source1);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[39].registre_source2);

    printf("test instruction 40\n");
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[40].format);
    UnityAssertEqualString("ECALL", instruction_bloc->instructions[40].nom,
                           "40", 40);

    printf("test instruction 41\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[41].format);
    UnityAssertEqualString("MUL", instruction_bloc->instructions[41].nom,
                           "41", 41);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[41].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[41].registre_source1);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[41].registre_source2);

    printf("test instruction 42\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[42].format);
    UnityAssertEqualString("MULH", instruction_bloc->instructions[42].nom,
                           "42", 42);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[42].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[42].registre_source1);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[42].registre_source2);

    printf("test instruction 43\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[43].format);
    UnityAssertEqualString("MULHSU", instruction_bloc->instructions[43].nom,
                           "43", 43);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[43].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[43].registre_source1);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[43].registre_source2);

    printf("test instruction 44\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[44].format);
    UnityAssertEqualString("MULHU", instruction_bloc->instructions[44].nom,
                           "44", 44);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[44].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[44].registre_source1);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[44].registre_source2);

    printf("test instruction 45\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[45].format);
    UnityAssertEqualString("DIV", instruction_bloc->instructions[45].nom,
                           "45", 45);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[45].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[45].registre_source1);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[45].registre_source2);

    printf("test instruction 46\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[46].format);
    UnityAssertEqualString("DIVU", instruction_bloc->instructions[46].nom,
                           "46", 46);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[46].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[46].registre_source1);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[46].registre_source2);

    printf("test instruction 47\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[47].format);
    UnityAssertEqualString("REM", instruction_bloc->instructions[47].nom,
                           "41", 47);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[47].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[47].registre_source1);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[47].registre_source2);

    printf("test instruction 48\n");
    TEST_ASSERT_EQUAL_INT(R, instruction_bloc->instructions[48].format);
    UnityAssertEqualString("REMU", instruction_bloc->instructions[48].nom,
                           "48", 48);
    TEST_ASSERT_EQUAL_INT(3,
                          instruction_bloc->instructions[48].registre_destination);
    TEST_ASSERT_EQUAL_INT(6,
                          instruction_bloc->instructions[48].registre_source1);
    TEST_ASSERT_EQUAL_INT(7,
                          instruction_bloc->instructions[48].registre_source2);

    strcpy(instruction_bloc->instructions[48].code_hexa, "0000000F");
    printf("instruction FENCE\n");
    decode_tableau_instructions(instruction_bloc->instructions, instruction_bloc->nb_instructions);
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[48].format);
    UnityAssertEqualString("FENCE", instruction_bloc->instructions[48].nom,
                           "48", 48);

    strcpy(instruction_bloc->instructions[48].code_hexa, "00100073");
    printf("instruction EBREAK\n");
    decode_tableau_instructions(instruction_bloc->instructions, instruction_bloc->nb_instructions);
    TEST_ASSERT_EQUAL_INT(I, instruction_bloc->instructions[48].format);
    UnityAssertEqualString("EBREAK", instruction_bloc->instructions[48].nom,
                           "48", 48);

    strcpy(instruction_bloc->instructions[48].code_hexa, "FFFFFFFF");
    printf("instruction mauvaise\n");
    decode_tableau_instructions(instruction_bloc->instructions, instruction_bloc->nb_instructions);
    TEST_ASSERT_EQUAL_INT(X, instruction_bloc->instructions[48].format);
    UnityAssertEqualString("", instruction_bloc->instructions[48].nom, "48",
                           48);

    free(instruction_bloc);
    instruction_bloc = NULL;
}


