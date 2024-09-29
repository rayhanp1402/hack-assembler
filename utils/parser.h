#ifndef PARSER_H
#define PARSER_H

#define MAX_ADDRESS_SIZE 6
#define MAX_DEST_SIZE 4
#define MAX_COMP_SIZE 8
#define MAX_JUMP_SIZE 4
#define MAX_LABEL_SIZE 31   // ANSI Standard
#define MAX_ROM_SIZE 5  // 32K ROM

// Structures
typedef struct Instruction {
    char addr[MAX_ADDRESS_SIZE];
    char dest[MAX_DEST_SIZE];
    char comp[MAX_COMP_SIZE];
    char jump[MAX_JUMP_SIZE];
} Instruction;

// Function prototypes
/**
 * Concatenates a single character to the end of a string.
 * 
 * @param string The string to which the character will be appended.
 * @param character The character to append to the string.
 */
void concatenate_character(char* string, char character);

/**
 * Parses a line of assembly code into an Instruction struct.
 * 
 * @param line The line of assembly code to parse.
 * @return A pointer to the parsed Instruction. The caller is responsible for freeing this memory.
 */
Instruction* parse_line_to_instruction(char* line);

/**
 * Parses a line of assembly code which contains a Label declaration into a Label Table.
 *
 * @param line The line of assembly code to parse.
 * @param labelTable A pointer to an existing Label Table. The caller is responsible for freeing this memory.
 * @param lineCounter A pointer to line counter, an integer which represents current ROM address being read.
 */
void parse_line_to_label(char* line, Table* labelTable, int* lineCounter);

/**
 * Frees the memory used by an Instruction struct.
 * 
 * @param instruction The instruction to free.
 */
void free_instruction(Instruction* instruction);

#endif