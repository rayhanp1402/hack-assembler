#include "table.h"
#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE_10 10
#define BITS_LENGTH 16

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

void assemble(Instruction* instruction) {
    char* assembledInstruction;

    if (strlen(instruction->addr) > 0) {
        char* endptr;
        long int num;

        num = strtol(instruction->addr, &endptr, BASE_10);

        assembledInstruction = to16Bits(num);

        printf("%s\n\n", assembledInstruction);

        free(assembledInstruction);
    } else {
        printf("Empty address\n\n");
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("Add.asm", "r");

    char myString[100];

    while(fgets(myString, 100, fptr)) {
        Instruction* instrTest = parse_line_to_instruction(myString);
        printf("Addr:%s\nDest:%s\nComp:%s\nJmp:%s\n", 
            instrTest->addr,
            instrTest->dest,
            instrTest->comp,
            instrTest->jump
        );
        assemble(instrTest);
    }

    fclose(fptr);

    return 0;
}