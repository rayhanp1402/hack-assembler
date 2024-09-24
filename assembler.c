#include "table.h"
#include "parser.h"

#include <stdio.h>

int main() {
    FILE *fptr;
    fptr = fopen("Add.asm", "r");

    char myString[100];

    while(fgets(myString, 100, fptr)) {
        Instruction* instrTest = parse_line_to_instruction(myString);
        printf("Addr:%s\nDest:%s\nComp:%s\nJmp:%s\n\n", 
            instrTest->addr,
            instrTest->dest,
            instrTest->comp,
            instrTest->jump
        );
    }

    fclose(fptr);

    return 0;
}