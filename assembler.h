#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "table.h"
#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE_10 10
#define BITS_LENGTH 16

// Function prototypes
/**
 * Converts a given integer to a 16-bit binary string.
 * 
 * @param num The integer to convert.
 * @return A pointer to a string representing the 16-bit binary number.
 *         The caller is responsible for freeing this memory.
 */
char* to16Bits(int num);

/**
 * Assembles an instruction (either A-type or C-type) into a 16-bit binary string.
 * 
 * @param instruction Pointer to an Instruction struct containing the components of the instruction.
 * @return A pointer to the assembled 16-bit binary string.
 *         The caller is responsible for freeing this memory.
 */
char* assemble(Instruction* instruction);

#endif