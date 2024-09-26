#include "table.h"
#include "parser.h"
#include "assembler.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* to16Bits(int num) {
    char* bits = (char*) malloc(sizeof(char) * (BITS_LENGTH + 1));
    bits[BITS_LENGTH] = '\0';

    for (int i = 0; i < BITS_LENGTH; ++i) {
        int mask = 1 << i;
        int maskedNum = num & mask;
        int bit = maskedNum >> i;

        bits[(BITS_LENGTH - 1) - i] = (bit) ? '1' : '0';
    }

    return bits;
}

char* assemble(Instruction* instruction) {
    if (strlen(instruction->addr) > 0) {
        char* assembledAInstruction;
        char* endptr;
        long int num;

        num = strtol(instruction->addr, &endptr, BASE_10);

        assembledAInstruction = to16Bits(num);

        return assembledAInstruction;
    }

    if (
        strlen(instruction->dest) > 0 ||
        strlen(instruction->comp) > 0 ||
        strlen(instruction->jump) > 0
    ) {
        char* assembledCInstruction = (char*) malloc(sizeof(char) * (BITS_LENGTH + 1));
        assembledCInstruction[0] = '1';
        assembledCInstruction[1] = '1';
        assembledCInstruction[2] = '1';
        assembledCInstruction[3] = '0';
        assembledCInstruction[4] = '0';
        assembledCInstruction[5] = '0';
        assembledCInstruction[6] = '0';
        assembledCInstruction[7] = '0';
        assembledCInstruction[8] = '0';
        assembledCInstruction[9] = '0';
        assembledCInstruction[10] = '0';
        assembledCInstruction[11] = '0';
        assembledCInstruction[12] = '0';
        assembledCInstruction[13] = '0';
        assembledCInstruction[14] = '0';
        assembledCInstruction[15] = '0';
        assembledCInstruction[16] = '\0';
        
        Table* destTable = initialize_table();
        insert_to_table("M", "001", destTable);
        insert_to_table("D", "010", destTable);
        insert_to_table("MD", "011", destTable);
        insert_to_table("A", "100", destTable);
        insert_to_table("AM", "101", destTable);
        insert_to_table("AD", "110", destTable);
        insert_to_table("AMD", "111", destTable);

        Table* compTable = initialize_table();
        insert_to_table("0", "0101010", compTable);
        insert_to_table("1", "0111111", compTable);
        insert_to_table("-1", "0111010", compTable);
        insert_to_table("D", "0001100", compTable);
        insert_to_table("A", "0110000", compTable);
        insert_to_table("!D", "0001101", compTable);
        insert_to_table("!A", "0110001", compTable);
        insert_to_table("-D", "0001111", compTable);
        insert_to_table("-A", "0110011", compTable);
        insert_to_table("D+1", "0011111", compTable);
        insert_to_table("A+1", "0110111", compTable);
        insert_to_table("D-1", "0001110", compTable);
        insert_to_table("A-1", "0110010", compTable);
        insert_to_table("D+A", "0000010", compTable);
        insert_to_table("D-A", "0010011", compTable);
        insert_to_table("A-D", "0000111", compTable);
        insert_to_table("D&A", "0000000", compTable);
        insert_to_table("D|A", "0010101", compTable);
        insert_to_table("M", "1110000", compTable);
        insert_to_table("!M", "1110001", compTable);
        insert_to_table("-M", "1110011", compTable);
        insert_to_table("M+1", "1110111", compTable);
        insert_to_table("M-1", "1110010", compTable);
        insert_to_table("D+M", "1000010", compTable);
        insert_to_table("D-M", "1010011", compTable);
        insert_to_table("M-D", "1000111", compTable);
        insert_to_table("D&M", "1000000", compTable);
        insert_to_table("D|M", "1010101", compTable);

        Table* jumpTable = initialize_table();
        insert_to_table("JGT", "001", jumpTable);
        insert_to_table("JEQ", "010", jumpTable);
        insert_to_table("JGE", "011", jumpTable);
        insert_to_table("JLT", "100", jumpTable);
        insert_to_table("JNE", "101", jumpTable);
        insert_to_table("JLE", "110", jumpTable);
        insert_to_table("JMP", "111", jumpTable);

        if (strlen(instruction->dest) > 0 && key_exists(instruction->dest, destTable)) {
            char* destBits = get_value(instruction->dest, destTable);
            assembledCInstruction[10] = destBits[0];
            assembledCInstruction[11] = destBits[1];
            assembledCInstruction[12] = destBits[2];
        }

        if (strlen(instruction->comp) > 0 && key_exists(instruction->comp, compTable)) {
            char* compBits = get_value(instruction->comp, compTable);
            assembledCInstruction[3] = compBits[0];
            assembledCInstruction[4] = compBits[1];
            assembledCInstruction[5] = compBits[2];
            assembledCInstruction[6] = compBits[3];
            assembledCInstruction[7] = compBits[4];
            assembledCInstruction[8] = compBits[5];
            assembledCInstruction[9] = compBits[6];
        }

        if (strlen(instruction->jump) > 0 && key_exists(instruction->jump, jumpTable)) {
            char* jumpBits = get_value(instruction->jump, jumpTable);
            assembledCInstruction[13] = jumpBits[0];
            assembledCInstruction[14] = jumpBits[1];
            assembledCInstruction[15] = jumpBits[2];
        }

        free_table(destTable);
        free_table(compTable);
        free_table(jumpTable);

        return assembledCInstruction;
    }
    
    return NULL;
}