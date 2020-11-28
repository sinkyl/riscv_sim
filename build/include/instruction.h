#ifndef PROJET1_INSTRUCTION_H
#define PROJET1_INSTRUCTION_H

#include <stdint.h>
#include <stdlib.h>


//structure pour les instructions loader du programme
enum format_t
{
    R, I, S, B, U, J, X
};

typedef struct
{
    char code_hexa[9];
    char nom[7];
    enum format_t format;

    uint32_t code_machine;
    uint32_t registre_source1;
    uint32_t registre_source2;
    uint32_t registre_destination;
    uint32_t immediat;
    uint32_t funct3;
    uint32_t funct7;
    uint32_t opcode;
} t_instruction;

//structure de table d'instructions pour le decodage
typedef struct
{
    const char *nom;
    uint32_t opcode;
    uint32_t funct3;
    uint32_t funct7;
    enum format_t format;
} table_intstructions_t;

typedef struct
{
    int nb_instructions;
    t_instruction *instructions;
} t_instruction_bloc;

#endif //PROJET1_INSTRUCTION_H
