#include "./data_structures/table.h"
#include "./utils/parser.h"
#include "./utils/assembler.h"

#define MAX_LINE_LENGTH 4096    // POSIX suggested

int main(int argc, char* argv[]) {
    if (argc == 3) {
        FILE* fptrInputFirstIteration;
        FILE* fptrInputSecondIteration;
        fptrInputFirstIteration = fopen(argv[1], "r");
        fptrInputSecondIteration = fopen(argv[1], "r");

        char line[MAX_LINE_LENGTH];

        int lineOfCodeCounter = 0;
        
        Table* labelTable = initialize_table();
        Table* variableTable = initialize_table();

        insert_to_table("R0", "0", variableTable);
        insert_to_table("R1", "1", variableTable);
        insert_to_table("R2", "2", variableTable);
        insert_to_table("R3", "3", variableTable);
        insert_to_table("R4", "4", variableTable);
        insert_to_table("R5", "5", variableTable);
        insert_to_table("R6", "6", variableTable);
        insert_to_table("R7", "7", variableTable);
        insert_to_table("R8", "8", variableTable);
        insert_to_table("R9", "9", variableTable);
        insert_to_table("R10", "10", variableTable);
        insert_to_table("R11", "11", variableTable);
        insert_to_table("R12", "12", variableTable);
        insert_to_table("R13", "13", variableTable);
        insert_to_table("R14", "14", variableTable);
        insert_to_table("R15", "15", variableTable);
        insert_to_table("SP", "0", variableTable);
        insert_to_table("LCL", "1", variableTable);
        insert_to_table("ARG", "2", variableTable);
        insert_to_table("THIS", "3", variableTable);
        insert_to_table("THAT", "4", variableTable);
        insert_to_table("SCREEN", "16384", variableTable);
        insert_to_table("KBD", "24576", variableTable);

        while(fgets(line, MAX_LINE_LENGTH, fptrInputFirstIteration)) {
            parse_line_to_label(line, labelTable, &lineOfCodeCounter);
        }

        fclose(fptrInputFirstIteration);

        while(fgets(line, MAX_LINE_LENGTH, fptrInputSecondIteration)) {
            FILE* fptrTarget;
            fptrTarget = fopen(argv[2], "a");

            parse_line_to_variable(line, variableTable, labelTable);

            Instruction* instruction = parse_line_to_instruction(line, variableTable, labelTable);
            char* assembledInstruction = assemble(instruction);

            if (assembledInstruction != NULL) {
                fprintf(fptrTarget, assembledInstruction);   
                fprintf(fptrTarget, "\n");
            }

            free(assembledInstruction);
            free_instruction(instruction);

            fclose(fptrTarget);
        }

        free_table(labelTable);
        free_table(variableTable);

        fclose(fptrInputSecondIteration);
    } else {
        fprintf(stderr, "Usage: %s <file_path> [input_file] <file_path> [target_file]\n", argv[0]);
    }

    return 0;
}