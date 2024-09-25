#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#define MAX_LINE_SIZE 4096  // POSIX suggested
#define MAX_ADDRESS_SIZE 6
#define MAX_DEST_SIZE 4
#define MAX_COMP_SIZE 8
#define MAX_JUMP_SIZE 4

typedef struct instruction {
    char addr[MAX_ADDRESS_SIZE];
    char dest[MAX_DEST_SIZE];
    char comp[MAX_COMP_SIZE];
    char jump[MAX_JUMP_SIZE];
} Instruction;

void concatenate_character(char* string, char character);

Instruction* parse_line_to_instruction(char* line);

void free_instruction(Instruction* instruction);

#endif