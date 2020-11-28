//
// Created by sinan on 2020-06-01.
//

#include "unity/unity.h"
#include "projet1.h"


void tearDown(void)
{

}


void setUp(void)
{

}


int main(void)
{
    UNITY_BEGIN();

    printf("********************************************************\n");
    printf("*              TESTS POUR DE DÉCODEUR                  *\n");
    printf("********************************************************\n");
    RUN_TEST(test_assemblage_instructions);
    RUN_TEST(test_decodage_instruction);

    printf("********************************************************\n");
    printf("*              TESTS POUR DE PROCESSEUR                  *\n");
    printf("********************************************************\n");
    //LOADS
    RUN_TEST(test_la_creation_dune_struct_de_processeur_initialle);
    RUN_TEST(test_load_byte_avec_immediate_positif);
    RUN_TEST(test_load_byte_avec_immediate_negatif);
    RUN_TEST(test_load_half_word_avec_immediate_positif);
    RUN_TEST(test_load_half_word_avec_immediate_negatif);
    RUN_TEST(test_load_word_avec_immediate_positif);
    RUN_TEST(test_load_word_avec_immediate_negatif);
    RUN_TEST(test_load_byte_unsigned_avec_immediate_positif);
    RUN_TEST(test_load_byte_unsigned_avec_immediate_negatif);
    RUN_TEST(test_load_word_unsigned_avec_immediate_positif);
    RUN_TEST(test_load_word_unsigned_avec_immediate_negatif);

    //STORES
    RUN_TEST(test_store_byte_avec_immediate_positif);
    RUN_TEST(test_store_byte_avec_immediate_negatif);
    RUN_TEST(test_store_half_word_avec_immediate_positif);
    RUN_TEST(test_store_half_word_avec_immediate_negatif);
    RUN_TEST(test_store_word_avec_immediate_positif);
    RUN_TEST(test_store_word_avec_immediate_negatif);

    //SHIFTS
    RUN_TEST(test_shift_left);
    RUN_TEST(test_shift_left_immediate);
    RUN_TEST(test_shift_right);
    RUN_TEST(test_shift_right_immediate);
    RUN_TEST(test_shift_right_arith);
    RUN_TEST(test_shift_right_arith_immediate);

    //ARITHMETIC
    RUN_TEST(test_addition);
    RUN_TEST(test_addition_immediate);
    RUN_TEST(test_subtract);
    RUN_TEST(test_load_upper_immediate);
    RUN_TEST(test_add_upper_imm_to_pc);

    //LOGICAL
    RUN_TEST(test_xor);
    RUN_TEST(test_xor_avec_immediate_positif);
    RUN_TEST(test_xor_avec_immediate_negatif);
    RUN_TEST(test_or);
    RUN_TEST(test_or_avec_immediate_positif);
    RUN_TEST(test_or_avec_immediate_negatif);
    RUN_TEST(test_and);
    RUN_TEST(test_and_avec_immediate_positif);
    RUN_TEST(test_and_avec_immediate_negatif);

    //COMPARE
    RUN_TEST(test_set);
    RUN_TEST(test_set_avec_immediate_positif);
    RUN_TEST(test_set_avec_immediate_negatif);
    RUN_TEST(test_set_usigned);
    RUN_TEST(test_set_unsigned_avec_immediate_positif);
    RUN_TEST(test_set_unsigned_avec_immediate_negatif);

    //BRANCHES
    RUN_TEST(test_branch_equal);
    RUN_TEST(test_branch_equal_sinon_pc_plus_4);
    RUN_TEST(test_branch_not_equal);
    RUN_TEST(test_branch_not_equal_sinon_pc_plus_4);
    RUN_TEST(test_branch_less_than);
    RUN_TEST(test_branch_less_than_sinon_pc_plus_4);
    RUN_TEST(test_branch_greater_or_equal);
    RUN_TEST(test_branch_greater_or_equal_sinon_pc_plus_4);
    RUN_TEST(test_branch_less_than_unsigned);
    RUN_TEST(test_branch_less_than_unsigned_sinon_pc_plus_4);
    RUN_TEST(test_branch_greater_or_equal_unsigned);
    RUN_TEST(test_branch_greater_or_equal_unsigned_sinon_pc_plus_4);

    //JUMPS
    RUN_TEST(test_jump_and_link);
    RUN_TEST(test_jump_and_link_register);

    return UNITY_END();
}