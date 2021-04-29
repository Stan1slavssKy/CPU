#include "assembler.h"

int main (int argc, char* argv[])
{
    text   asm_file = {};
    char* file_name = console_input (argc, argv);

    assembler_read (&asm_file, file_name);
    assembler_free (&asm_file);

    return 0;
}