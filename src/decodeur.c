#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/decodeur.h"

//table des instructions pour le decodage
table_intstructions_t table_intstructions[] = {
        {"LUI",    0b0110111, 0,     0,         U},
        {"AUIPC",  0b0010111, 0,     0,         U},
        {"JAL",    0b1101111, 0,     0,         J},
        {"JALR",   0b1100111, 0,     0,         I},
        {"BEQ",    0b1100011, 0,     0,         B},
        {"BNE",    0b1100011, 0b001, 0,         B},
        {"BLT",    0b1100011, 0b100, 0,         B},
        {"BGE",    0b1100011, 0b101, 0,         B},
        {"BLTU",   0b1100011, 0b110, 0,         B},
        {"BGEU",   0b1100011, 0b111, 0,         B},
        {"LB",     0b0000011, 0b000, 0,         I},
        {"LH",     0b0000011, 0b001, 0,         I},
        {"LW",     0b0000011, 0b010, 0,         I},
        {"LBU",    0b0000011, 0b100, 0,         I},
        {"LHU",    0b0000011, 0b101, 0,         I},
        {"SB",     0b0100011, 0,     0,         S},
        {"SH",     0b0100011, 0b001, 0,         S},
        {"SW",     0b0100011, 0b010, 0,         S},
        {"ADDI",   0b0010011, 0,     0,         I},
        {"SLTI",   0b0010011, 0b010, 0,         I},
        {"SLTIU",  0b0010011, 0b011, 0,         I},
        {"XORI",   0b0010011, 0b100, 0,         I},
        {"ORI",    0b0010011, 0b110, 0,         I},
        {"ANDI",   0b0010011, 0b111, 0,         I},
        {"SLLI",   0b0010011, 0b001, 0,         I},
        {"SRLI",   0b0010011, 0b101, 0,         I},
        {"SRAI",   0b0010011, 0b101, 0b0100000, I},
        {"ADD",    0b0110011, 0,     0,         R},
        {"SUB",    0b0110011, 0,     0b0100000, R},
        {"SLL",    0b0110011, 0b001, 0,         R},
        {"SLT",    0b0110011, 0b010, 0,         R},
        {"SLTU",   0b0110011, 0b011, 0,         R},
        {"XOR",    0b0110011, 0b100, 0,         R},
        {"SRL",    0b0110011, 0b101, 0,         R},
        {"SRA",    0b0110011, 0b101, 0b0100000, R},
        {"OR",     0b0110011, 0b110, 0,         R},
        {"AND",    0b0110011, 0b111, 0,         R},
        {"FENCE",  0b0001111, 0,     0,         I},
        {"ECALL",  0b1110011, 0,     0,         I},
        {"EBREAK", 0b1110011, 0,     1,         I},
        {"MUL",    0b0110011, 0,     0b0000001, R},
        {"MULH",   0b0110011, 0b001, 0b0000001, R},
        {"MULHSU", 0b0110011, 0b010, 0b0000001, R},
        {"MULHU",  0b0110011, 0b011, 0b0000001, R},
        {"DIV",    0b0110011, 0b100, 0b0000001, R},
        {"DIVU",   0b0110011, 0b101, 0b0000001, R},
        {"REM",    0b0110011, 0b110, 0b0000001, R},
        {"REMU",   0b0110011, 0b111, 0b0000001, R},
        {NULL,     0,         0,     0,         X}};

/**********************************************************
*             PROTOTYPES FONCTIONS PRIVÉES
**********************************************************/
/** Fonction pour interface externe
 * permet de decoder une instruction qui a ete lu dans un fichier txt
 * @param instruction instruction a decoder
 * @return 1 si l'operation est un succes sinon 0
 */
int decode_instruction(t_instruction *instruction);

/**
 *
 * @param instruction pointeur sur instruction a trouver dans la table
 * @param niveau_de_recherche different niveau de recherche dans la table selon
 * les conditions (voir les ifs dans l implementation)
 * @return 1 si trouver dans la table ou 0 sinon
 */
int cherche_table_intstructions(
        t_instruction *instruction,
        uint32_t niveau_de_recherche);

/** Implementation maison de la fonction strtol
 *
 * @param code_hexa chaine de caractere du code machine en hexadecimal
 * @return le code machine correspondant en 32bits
 */
uint32_t hexa_a_32bits(char *code_hexa);

/**
 * fabrique des masqque de 4 bits pour un 32 bits selon l index
 * l'index etant la position du paquet de 4 bits voulu dans le 32bits
 * (fonction qui accompagne hexa_a_32bits)
 * @param valeur_dec voulu pour le masque
 * @param index ex: 0 etant le paquet de 4 bits le moins significatifs et 7 le
 * paquet le plus significatif
 * @return le masque fabriquer
 */
uint32_t fabriquer_masque_hexa_binaire(uint32_t valeur_dec, uint32_t index);


/**fabrique les immediats selon le format d'encodage
 *
 * @param format format de l'encodage de l'instruction
 * @param code_machine en format uint_32t
 * @return retourne l'immediat sur 32bits
 */
signed fabrique_imm32bits(enum format_t format, uint32_t code_machine);


/**
 * Partitionne l'instruction selon des champs generaux
 * @param instruction l'instruction a partitioner
 * @return 1
 */
int partitione_code_machine_a_instruction(t_instruction *instruction);

/**
 * Permet d'obtenir le nombre d'instruction dans un fichier
 * @param fichier   le nom du fichier qui se trouve dans
 *        le répertoire "input"
 * @return le nombre d instructions dans le fichier texte
 */
int nb_instructions_dans_fichier(FILE *fichier);


/**********************************************************
*           IMPLÉMENTATION DES FONCTIONS PUBLIC
**********************************************************/

t_instruction_bloc *assemblage_instructions(char *nom_fichier)
{
    FILE *fichier = NULL;

    fichier = fopen(nom_fichier, "r+");

    if (fichier == NULL)
    {
        perror("Incapable d ouvrir le fichier! \n");
        return NULL;
    }

    int nb_i = nb_instructions_dans_fichier(fichier);

    t_instruction_bloc *instruction_bloc = (t_instruction_bloc *) malloc(
            sizeof(t_instruction_bloc));
    t_instruction *instructions = (t_instruction *) malloc(
            nb_i * sizeof(t_instruction));

    if (instructions == NULL || instruction_bloc == NULL)
    {
        perror("Erreur d'obtention de la mémoire ! \n");
        exit(-1);
    }

    instruction_bloc->instructions = instructions;
    instruction_bloc->nb_instructions = nb_i;

    char hexa[11];
    int i = 0;
    while (fgets(hexa, sizeof(hexa), fichier))
    {
        hexa[8] = '\0';
        strcpy(instruction_bloc->instructions[i].code_hexa, hexa);
        i++;

    }

    fclose(fichier);
    return instruction_bloc;
}


int decode_instruction(t_instruction *instruction)
{
    uint32_t r_val = 0;

    instruction->code_machine = hexa_a_32bits(instruction->code_hexa);
    partitione_code_machine_a_instruction(instruction);

    if (instruction->opcode == 0b1110011)
        //cas special ECALL/EBREAK
    {
        r_val = cherche_table_intstructions(instruction, 3);

    }
    else if (instruction->opcode == 0b0110011 ||
             (instruction->opcode == 0b0010011 && instruction->funct3 == 0b101))
        //cas special R ou cas de SRLI/SRAI
    {
        r_val = cherche_table_intstructions(instruction, 2);

    }
    else if (instruction->opcode == 0b0110111 ||
             instruction->opcode == 0b0010111 ||
             instruction->opcode == 0b1101111)
        //cas special U et J
    {
        r_val = cherche_table_intstructions(instruction, 0);

    }
    else
    {
        r_val = cherche_table_intstructions(instruction, 1);

    }

    instruction->immediat = fabrique_imm32bits(instruction->format,
                                               instruction->code_machine);
    return r_val;
}


void
decode_tableau_instructions(t_instruction *instruction, int nb_instructions)
{
    for (int i = 0; i < nb_instructions; i++)
    {
        decode_instruction(&instruction[i]);
    }
}

/**********************************************************
*           IMPLÉMENTATION DES FONCTIONS PRIVE
**********************************************************/
signed fabrique_imm32bits(enum format_t format, uint32_t code_machine)
{
    uint32_t imm_32bits = 0;

    switch (format)
    {
        case I:
            imm_32bits = (code_machine >> 31 == 0) ? 0 : (imm_32bits |
                                                          0xFFFFF800);
            imm_32bits = imm_32bits + (code_machine >> 20 & 0x7FF);
            break;

        case S:
            imm_32bits = (code_machine >> 31 == 0) ? 0 : (imm_32bits |
                                                          0xFFFFF800);
            imm_32bits = imm_32bits + (((code_machine >> 25 & 0x3F) << 5)
                                       | (code_machine >> 7 & 0x1F));
            break;

        case B:
            imm_32bits = (code_machine >> 31 == 0) ? 0 : (imm_32bits |
                                                          0xFFFFF000);
            imm_32bits = imm_32bits + (((code_machine >> 7 & 0x1) << 11)
                                       | ((code_machine >> 25 & 0x3F) << 5)
                                       | (code_machine >> 7 & 0x1E));
            break;

        case U:
            imm_32bits = (code_machine & 0xFFFFF000);
            break;

        case J:
            imm_32bits = (code_machine >> 31 == 0) ? 0 : (imm_32bits |
                                                          0xFFF00000);
            imm_32bits = imm_32bits + (((code_machine >> 12 & 0xFF) << 12)
                                       | ((code_machine >> 20 & 0x1) << 11)
                                       | (code_machine >> 20 & 0x7FE));
            break;

        default:
            return 0;

    }

    return imm_32bits;
}


int partitione_code_machine_a_instruction(t_instruction *instruction)
{

    instruction->registre_source1 = instruction->code_machine >> 15 & 0x1F;
    instruction->registre_source2 = instruction->code_machine >> 20 & 0x1F;
    instruction->registre_destination = instruction->code_machine >> 7 & 0x1F;
    instruction->opcode = instruction->code_machine & 0x7F;;
    instruction->funct3 = instruction->code_machine >> 12 & 0x7;
    instruction->funct7 = instruction->code_machine >> 25 & 0x7F;
    instruction->immediat = instruction->code_machine >> 20 & 0xFFF;
    return 1;
}


uint32_t hexa_a_32bits(char *code_hexa)
{
    uint32_t instruction_32bits = 0;
    uint32_t masque = 0;
    uint32_t index_hexa_bin = 0;

    for (int i = (int) strlen(code_hexa) - 1; i >= 0; i--)
    {
        if (code_hexa[i] - '0' > 9)
        {
            switch (code_hexa[i])
            {
                case 'a':
                case 'A':
                    masque = fabriquer_masque_hexa_binaire(10, index_hexa_bin);
                    instruction_32bits = instruction_32bits | masque;
                    break;
                case 'b':
                case 'B':
                    masque = fabriquer_masque_hexa_binaire(11, index_hexa_bin);
                    instruction_32bits = instruction_32bits | masque;
                    break;
                case 'c':
                case 'C':
                    masque = fabriquer_masque_hexa_binaire(12, index_hexa_bin);
                    instruction_32bits = instruction_32bits | masque;
                    break;
                case 'd':
                case 'D':
                    masque = fabriquer_masque_hexa_binaire(13, index_hexa_bin);
                    instruction_32bits = instruction_32bits | masque;
                    break;
                case 'e':
                case 'E':
                    masque = fabriquer_masque_hexa_binaire(14, index_hexa_bin);
                    instruction_32bits = instruction_32bits | masque;
                    break;
                case 'f':
                case 'F':
                    masque = fabriquer_masque_hexa_binaire(15, index_hexa_bin);
                    instruction_32bits = instruction_32bits | masque;
                    break;
            }
        }
        else
        {
            masque = fabriquer_masque_hexa_binaire(code_hexa[i] - '0',
                                                   index_hexa_bin);
            instruction_32bits = instruction_32bits | masque;

        }

        index_hexa_bin++;
    }

    return instruction_32bits;
}


int cherche_table_intstructions(
        t_instruction *instruction,
        uint32_t niveau_de_recherche)
{
    int trouver = 0;

    if (niveau_de_recherche == 0)
    {
        for (table_intstructions_t *element = table_intstructions;
             element->nom != NULL; ++element)
        {
            if (element->opcode == instruction->opcode)
            {
                strcpy(instruction->nom, element->nom);
                instruction->format = element->format;
                trouver = 1;
            }
        }

    }
    else if (niveau_de_recherche == 1)
    {
        for (table_intstructions_t *element = table_intstructions;
             element->nom != NULL; ++element)
        {
            if (element->opcode == instruction->opcode &&
                element->funct3 == instruction->funct3)
            {
                strcpy(instruction->nom, element->nom);
                instruction->format = element->format;
                trouver = 1;
            }
        }

    }
    else if (niveau_de_recherche == 2)
    {
        for (table_intstructions_t *element = table_intstructions;
             element->nom != NULL; ++element)
        {
            if (element->opcode == instruction->opcode &&
                element->funct3 == instruction->funct3 &&
                element->funct7 == instruction->funct7)
            {
                strcpy(instruction->nom, element->nom);
                instruction->format = element->format;
                trouver = 1;
            }
        }

    }
    else
    {
        for (table_intstructions_t *element = table_intstructions;
             element->nom != NULL; ++element)
        {
            if (element->opcode == instruction->opcode &&
                element->funct7 == instruction->immediat)
            {
                strcpy(instruction->nom, element->nom);
                instruction->format = element->format;
                trouver = 1;
            }
        }
    }

    if (!trouver)
    {
        strcpy(instruction->nom, "");
        instruction->format = X;
    }
    return trouver;
}


uint32_t fabriquer_masque_hexa_binaire(uint32_t valeur_dec, uint32_t index)
{
    uint32_t masque;
    masque = valeur_dec;

    if (index > 0)
    {
        for (int i = 1; i <= index; i++)
        {
            masque = masque * 16;
        }
    }

    return masque;
}

int nb_instructions_dans_fichier(FILE *fichier)
{
    size_t nb_instructions = 0;
    char tampon[11];

    while (fgets(tampon, sizeof(tampon), fichier))
    {
        nb_instructions++;
    }

    fseek(fichier, 0, SEEK_SET);
    return nb_instructions;
}