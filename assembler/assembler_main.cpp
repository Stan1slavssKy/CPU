#include "assembler.h"

int main ()
{
    struct file asm_file = {};
    char   file_name[17] = "../txt files/asm";
    struct str* data     = assembler_read (&asm_file, file_name);
  
    assembler_free (asm_file.file_buffer, data);
}