#include "assembler.h"

void assembler_read (text* asm_file, char* file_name)
{
    input_inform (file_name, asm_file);
    int nmb_spaces = skip_spaces (asm_file);
    asm_file_analize (asm_file, nmb_spaces);
}

//=====================================================================================================

void asm_file_analize (text* asm_file, int nmb_spaces)
{
    char*   buffer    = asm_file -> file_buffer;
    double* byte_code = (double*) calloc (asm_file -> size_of_file, sizeof (double));
    
    int idx     = 0;
    int counter = 0;

    char* cmd = strtok (buffer, " ");
    printf ("%s", cmd);

    byte_code[idx++] = ' ';
    byte_code[idx++] = assembling (cmd);

    while (1)
    {
        cmd = strtok (nullptr, " ");
        printf ("%s", cmd);

        if (isdigit (*cmd))
        {
            double nmb = atof (cmd);
            byte_code[idx++] = ' ';
            byte_code[idx++] = nmb;
        }
        else
        {
            byte_code[idx++] = ' ';
            byte_code[idx++] = assembling (cmd);
        }

        counter++;
        if (counter == nmb_spaces)
        {
            break;
        }
    }

    printf ("\n");

    for (int i = 0; i < asm_file -> size_of_file; i++)
    printf ("{%lg}\n", byte_code[i]);
    
    input_b_file (asm_file, byte_code);
    free (byte_code);
}  

//=====================================================================================================

double assembling (char* cmd)
{
    using namespace my_commands;

    if (0) {}
    
    GET_COMMAND (push, PUSH)
    GET_COMMAND (pop, POP)
    GET_COMMAND (add, ADD)
    GET_COMMAND (sub, SUB)
    GET_COMMAND (div, DIV)
    GET_COMMAND (out, OUT)
    GET_COMMAND (hlt, HLT)
    GET_COMMAND (end, END)
    GET_COMMAND (unknown_cmd, UNKNOWN_CMD)
    
    return -1;
}

//=====================================================================================================

void input_b_file (text* asm_file, double* byte_code)
{
    FILE* file = fopen ("../txt files/asm_binary", "wb");
    assert (file != nullptr);
   
    fwrite (byte_code, sizeof (double), asm_file -> size_of_file, file);

    fclose (file);
}

//=====================================================================================================

void assembler_free (text* asm_file)
{
    free (asm_file -> file_buffer);
    asm_file -> file_buffer = nullptr;
    
    free (asm_file -> strings);
    asm_file -> strings = nullptr;
}              

//=====================================================================================================