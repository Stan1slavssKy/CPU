#include "assembler.h"

int main ()
{
    struct file asm_file = {};
    char   file_name[17] = "../txt files/asm";
    struct string* data  = assembler_construct (&asm_file, file_name);
  
    assembler_destruct (asm_file.file_buffer, data);
}