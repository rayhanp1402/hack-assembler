#include "./data_structures/table.h"
#include "./utils/parser.h"
#include "./utils/assembler.h"

#define MAX_LINE_LENGTH 4096    // POSIX suggested

int main(int argc, char* argv[]) {
    if (argc == 3) {
        FILE* fptrInput;
        fptrInput = fopen(argv[1], "r");

        char line[MAX_LINE_LENGTH];

        while(fgets(line, MAX_LINE_LENGTH, fptrInput)) {
            FILE* fptrTarget;
            fptrTarget = fopen(argv[2], "a");

            Instruction* instruction = parse_line_to_instruction(line);
            char* assembledInstruction = assemble(instruction);

            if (assembledInstruction != NULL) {
                fprintf(fptrTarget, assembledInstruction);   
                fprintf(fptrTarget, "\n");
            }

            free(assembledInstruction);
            free_instruction(instruction);

            fclose(fptrTarget);
        }

        fclose(fptrInput);
    } else {
        fprintf(stderr, "Usage: %s <file_path> [input_file] <file_path> [target_file]\n", argv[0]);
    }

    return 0;
}