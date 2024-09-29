#include "../data_structures/table.h"
#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

void concatenateCharacter(char* string, char character) {
    int stringLength = strlen(string);
    string[stringLength + 1] = '\0';
    string[stringLength] = character;
}

bool isNumber(char* string) {
    for (int i = 0; i < strlen(string); ++i) {
        if (!isdigit(string[i])) return false;
    }
    return true;
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
            concatenateCharacter(instruction->addr, line[i]);
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
            concatenateCharacter(tempString, line[i]);
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

void parse_line_to_label(char* line, Table* labelTable, int* lineCounter) {
    int lineLength = strlen(line);
    bool isReadingLabel = false;
    bool isInstruction = false;

    char* label = (char*) malloc(sizeof(char) * MAX_SYMBOL_SIZE);
    label[0] = '\0';
    
    for (int i = 0; i < lineLength; ++i) {
        if (line[i] == '\n' || line[i] == ')') break;

        if (isspace(line[i])) continue;

        if (i < lineLength - 1 && line[i] == '/' && line[i+1] == '/') {
            break;  // Terminate when comment is found
        }

        if (line[i] == '@' || line[i] == '=' || line[i] == ';') {
            isReadingLabel = false;
            (*lineCounter)++;
            break;
        }

        if (line[i] == '(') {
            isReadingLabel = true;
            continue;
        }

        if (isReadingLabel) {
            concatenateCharacter(label, line[i]);
        }
    }

    if (strlen(label) > 0 && isReadingLabel) {
        char* romAddress = (char*) malloc(sizeof(char) * MAX_ROM_SIZE);
        romAddress[0] = '\0';
        sprintf(romAddress, "%d", *lineCounter);
        insert_to_table(label, romAddress, labelTable);
    }
}

void parse_line_to_variable(char* line, Table* variableTable, Table* labelTable) {
    int lineLength = strlen(line);
    bool isAInstruction = false;

    char* variable = (char*) malloc(sizeof(char) * MAX_SYMBOL_SIZE);
    variable[0] = '\0';
    
    for (int i = 0; i < lineLength; ++i) {
        if (line[i] == '\n' || line[i] == ')') break;

        if (isspace(line[i])) continue;

        if (i < lineLength - 1 && line[i] == '/' && line[i+1] == '/') {
            break;  // Terminate when comment is found
        }

        if (line[i] == '@') {
            isAInstruction = true;
            continue;
        }

        if (isAInstruction) {
            concatenateCharacter(variable, line[i]);
        }
    }

    if (isAInstruction && !isNumber(variable)) {
        if (!key_exists(variable, variableTable) && !key_exists(variable, labelTable)) {
            char* address = (char*) malloc(sizeof(char) * MAX_ADDRESS_SIZE);
            address[0] = '\0';
            sprintf(address, "%d", (variableTable->size) - 1);
            insert_to_table(variable, address, variableTable);
        }
    }
}

void free_instruction(Instruction* instruction) {
    free(instruction);
}