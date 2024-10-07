# HACK-Assembler

Assembler for the HACK Assembly Language from [nand2tetris](https://www.nand2tetris.org/).

Note: No syntax error detection

## Compilation

You may compile the main program using any C compiler.

GCC example:

```bash
    gcc main.c .../data_structures/table.c ../utils/parser.c ../utils/assembler.c -o main
```

Note: Include table.c, parser.c, and assembler.c during compilation. The file structure is shown below.

```bash
.
├── README.md
├── data_structures
│ ├── table.c
│ └── table.h
├── main.c
├── main.exe
└── utils
├── assembler.c
├── assembler.h
├── parser.c
└── parser.h
```

## Usage

```bash
    <executable> <file_path> [input_file] <file_path> [target_file]
```

Example:

```bash
    ./main ./asm_files/Pong.asm ./bin/Pong.bin
```

Note:

- If the target file does not exist yet, the assembler will create it.
- If the target file exists, the assembler will APPEND the machine code into the file.

## Expected Behavior

Example:

### Rect.asm

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/6/rect/Rect.asm

// Draws a rectangle at the top-left corner of the screen.
// The rectangle is 16 pixels wide and R0 pixels high.
// Usage: Before executing, put a value in R0.

   // If (R0 <= 0) goto END else n = R0
   @R0
   D=M
   @END
   D;JLE
   @n
   M=D
   // addr = base address of first screen row
   @SCREEN
   D=A
   @addr
   M=D
(LOOP)
   // RAM[addr] = -1
   @addr
   A=M
   M=-1
   // addr = base address of next screen row
   @addr
   D=M
   @32
   D=D+A
   @addr
   M=D
   // decrements n and loops
   @n
   MD=M-1
   @LOOP
   D;JGT
(END)
   @END
   0;JMP
```

Will turn the assembly code into the following machine code:

```
0000000000000000
1111110000010000
0000000000010111
1110001100000110
0000000000010000
1110001100001000
0100000000000000
1110110000010000
0000000000010001
1110001100001000
0000000000010001
1111110000100000
1110111010001000
0000000000010001
1111110000010000
0000000000100000
1110000010010000
0000000000010001
1110001100001000
0000000000010000
1111110010011000
0000000000001010
1110001100000001
0000000000010111
1110101010000111
```
