#include "assembler.h"

void assembler_read (text* asm_file, char* file_name)
{
    //ASSERT
    input_inform (file_name, asm_file);
    
    lexsemes* cmd_lexem = (lexsemes*) calloc (asm_file -> size_of_file, sizeof (lexsemes));
   // ASSERT
    
    asm_file_analize (asm_file, cmd_lexem);
    free (cmd_lexem);
}

//=====================================================================================================

void asm_file_analize (text* asm_file, lexsemes* cmd_lexem) // push 5
{
    char*   buffer    = asm_file -> file_buffer;
    double* byte_code = (double*) calloc (asm_file -> size_of_file, sizeof (double));
    
    int idx     = 0;
    int counter = 0;

    char* cmd = strtok (buffer, " \n");
    cmd_lexem -> lexsem_name = cmd;
    printf ("%s", cmd);

    byte_code[idx++] = asm_c::assembling (cmd_lexem, cmd, 0);

    while (1)
    {
        cmd = strtok (nullptr, " \n");
        if (cmd == nullptr)
        {
            break;
        }

        cmd_lexem -> lexsem_name = cmd;
        printf ("%s", cmd);

        if (isdigit (*cmd))
        {
            double nmb = atof (cmd);
            byte_code[idx++] = nmb;
            asm_c::assembling (cmd_lexem, nullptr, nmb);
        }
        else
        {
            byte_code[idx++] = asm_c::assembling (cmd_lexem, cmd, 0);
        }
    }

    printf ("\n");

    input_b_file (asm_file, byte_code);
    free (byte_code);
}  

//=====================================================================================================

double asm_c::assembling (lexsemes* cmd_lexem, char* cmd, int number)
{
    if (cmd != nullptr)
    {
        if (0) {} 

        GET_COMMAND (push, PUSH, 0)
        GET_COMMAND (pop, POP, 0)
        GET_COMMAND (add, ADD, 0)
        GET_COMMAND (sub, SUB, 0)
        GET_COMMAND (div, DIV, 0)
        GET_COMMAND (mul, MUL, 0)
        GET_COMMAND (out, OUT, 0)
        GET_COMMAND (hlt, HLT, 0)
        GET_COMMAND (end, END, 0)
        GET_COMMAND (unknown_cmd, UNKNOWN_CMD, 0)
    }

    else 
    {                                                    
        checking_lex_type (cmd_lexem, NUMBER, number);                            
    } 

    return -1;
}

//=====================================================================================================

void asm_c::checking_lex_type (lexsemes* cmd_lexem, int CMD_ENUM, int number)
{
    if (CMD_ENUM != NUMBER)
    {
        switch (CMD_ENUM)
        {
            TYPE_COMMAND (PUSH, N_COMMAND)
            TYPE_COMMAND (DIV,    COMMAND)
            TYPE_COMMAND (MUL,    COMMAND)
            TYPE_COMMAND (SUB,    COMMAND)
            TYPE_COMMAND (POP,    COMMAND)
            TYPE_COMMAND (ADD,    COMMAND)
            TYPE_COMMAND (OUT,    COMMAND)
            TYPE_COMMAND (HLT,    COMMAND)
            TYPE_COMMAND (END,    COMMAND)

            default:
            {
                printf ("Error in checking_lex_type\n");
            }
        }
    }

    else
    {
        cmd_lexem -> lexsem_type = NUMBER;
    }
}

//=====================================================================================================

void input_b_file (text* asm_file, double* byte_code)
{
    FILE* file = fopen ("../txt files/asm_binary", "wb");
    assert (file);

    for (int i = 0; i < asm_file -> size_of_file; i++)
        printf ("{%lg}\n", byte_code[i]);

    fwrite (byte_code, sizeof (double), asm_file -> size_of_file, file);

    fclose(file);
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