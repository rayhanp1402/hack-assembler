#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

void concatenate_character(char* string, char character) {
    int stringLength = strlen(string);
    string[stringLength + 1] = '\0';
    string[stringLength] = character;
}

Instruction* parse_line_to_instruction(char* line) {
    Instruction* instruction = (Instruction*) malloc(sizeof(Instruction));
    instruction->addr[0] = '\0';
    instruction->dest[0] = '\0';
    instruction->comp[0] = '\0';
    instruction->jump[0] = '\0';

    // Stores current C-Instruction before knowing if is it dest/comp/jmp
    char tempString[MAX_DEST_SIZE + MAX_COMP_SIZE + MAX_JUMP_SIZE + 2] = "";

    int lineLength = strlen(line);
    bool isAInstruction = false;
    bool includeJump = false;
    for (int i = 0; i < lineLength; ++i) {
        if (line[i] == '\n') break;

        if (isspace(line[i])) continue;

        if (i < lineLength - 1 && line[i] == '/' && line[i+1] == '/') {
            break;  // Terminate when comment is found
        }

        if (line[i] == '@') {
            isAInstruction = true;
            continue;
        }

        if (isAInstruction) {
            concatenate_character(instruction->addr, line[i]);
            continue;
        }

        if (line[i] == '=') {
            strcat(instruction->dest, tempString);
            tempString[0] = '\0';
        } else if (line[i] == ';') {
            strcat(instruction->comp, tempString);
            tempString[0] = '\0';
            includeJump = true;
        } else {
            concatenate_character(tempString, line[i]);
        }
    }

    if (!isAInstruction) {
        if (includeJump) {
            strcat(instruction->jump, tempString);
        } else {
            strcat(instruction->comp, tempString);
        }
    }

    return instruction;
}

void free_instruction(Instruction* instruction) {
    free(instruction);
}