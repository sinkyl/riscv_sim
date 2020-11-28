#ifndef PROJET1_PROJET1_H
#define PROJET1_PROJET1_H

/*******************************************************************************
 *                  Prototypes de test pour decodeur
 * ****************************************************************************/
void test_assemblage_instructions(void);

void test_decodage_instruction(void);

/*******************************************************************************
 *                  Prototypes de test pour processeur
 * ****************************************************************************/
void test_la_creation_dune_struct_de_processeur_initialle(void);
void test_load_byte_avec_immediate_positif(void);
void test_load_byte_avec_immediate_negatif(void);
void test_load_half_word_avec_immediate_positif(void);
void test_load_half_word_avec_immediate_negatif(void);
void test_load_word_avec_immediate_positif(void);
void test_load_word_avec_immediate_negatif(void);
void test_load_byte_unsigned_avec_immediate_positif(void);
void test_load_byte_unsigned_avec_immediate_negatif(void);
void test_load_word_unsigned_avec_immediate_positif(void);
void test_load_word_unsigned_avec_immediate_negatif(void);

void test_store_byte_avec_immediate_positif(void);
void test_store_byte_avec_immediate_negatif(void);
void test_store_half_word_avec_immediate_positif(void);
void test_store_half_word_avec_immediate_negatif(void);
void test_store_word_avec_immediate_positif(void);
void test_store_word_avec_immediate_negatif(void);

void test_shift_left(void);
void test_shift_left_immediate(void);
void test_shift_right(void);
void test_shift_right_immediate(void);
void test_shift_right_arith(void);
void test_shift_right_arith_immediate(void);

void test_addition(void);
void test_addition_immediate(void);
void test_subtract(void);
void test_load_upper_immediate(void);
void test_add_upper_imm_to_pc(void);

void test_xor(void);
void test_xor_avec_immediate_positif(void);
void test_xor_avec_immediate_negatif(void);
void test_or(void);
void test_or_avec_immediate_positif(void);
void test_or_avec_immediate_negatif(void);
void test_and(void);
void test_and_avec_immediate_positif(void);
void test_and_avec_immediate_negatif(void);

void test_set(void);
void test_set_avec_immediate_negatif(void);
void test_set_avec_immediate_positif(void);
void test_set_usigned(void);
void test_set_unsigned_avec_immediate_positif(void);
void test_set_unsigned_avec_immediate_negatif(void);

void test_branch_equal(void);
void test_branch_equal_sinon_pc_plus_4(void);
void test_branch_not_equal(void);
void test_branch_not_equal_sinon_pc_plus_4(void);
void test_branch_less_than(void);
void test_branch_less_than_sinon_pc_plus_4(void);
void test_branch_greater_or_equal(void);
void test_branch_greater_or_equal_sinon_pc_plus_4(void);
void test_branch_less_than_unsigned(void);
void test_branch_less_than_unsigned_sinon_pc_plus_4(void);
void test_branch_greater_or_equal_unsigned(void);
void test_branch_greater_or_equal_unsigned_sinon_pc_plus_4(void);

void test_jump_and_link(void);
void test_jump_and_link_register(void);

#endif //PROJET1_PROJET1_H
