#include "assembler.h"

int main (int argc, char* argv[])
{
    struct file asm_file = {};
    //char   file_name[17] = "../txt files/asm";
    char* file_name = "";
    
    if (argc == 2)
    {
        file_name = argv[1];
        printf ("You want read \"%s\"\n", file_name);
    }
    else if (argc == 1)
    {
        printf ("You didn't enter the file name. Please return program and enter file name.\n");
        return 0;
    }
    else
    {
        printf ("Error to few or too many arguments.\n");
        return 0;
    }

    struct str* data     = assembler_read (&asm_file, file_name);
  
    assembler_free (asm_file.file_buffer, data);
}
