#include "assembler.h"

void assembler_read (text* asm_file, char* file_name)
{
    assert (file_name);
    assert (asm_file);

    input_inform (file_name, asm_file);
    asm_file_analize (asm_file);
}

//=====================================================================================================

void asm_file_analize (text* asm_file) 
{
    assert (asm_file);
    assert (asm_file -> file_buffer);
   
    char*   cmd       = nullptr;
    double  nmb       = 0;
    char*   buffer    = asm_file -> file_buffer;
    
    double* byte_code = (double*) calloc (asm_file -> size_of_file, sizeof (double));
    assert (byte_code);
   
    parsing_lexems (asm_file);
    assert (asm_file -> lexem);

    for (int i = 0; i < asm_file -> number_lexems; i++)
    {
        cmd = (asm_file -> lexem + i) -> lexem_name;

        if (isdigit (*cmd))
        {
            nmb = atof (cmd);
            printf ("nmb is %lg\n", nmb);
            byte_code [i] = asm_cmd::assembling (asm_file, nullptr, nmb, asm_file -> lexem + i);
        }
        else
        {  
            printf ("cmd is %s\n", cmd);
            byte_code [i] = asm_cmd::assembling (asm_file, cmd, 0, asm_file -> lexem + i);
        } 
    }

    input_b_file (asm_file, byte_code);
    free (byte_code);
}  

//=====================================================================================================

double asm_cmd::assembling (text* asm_file, char* cmd, int number, lexemes* lexem_i)
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
        checking_lex_type (asm_file, NUMBER, number, lexem_i);    
        return number;                        
    } 

    return -1;
}

//=====================================================================================================

void asm_cmd::checking_lex_type (text* asm_file, int CMD_ENUM, int number, lexemes* lexem_i)
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
        lexem_i -> lexem_type = NUMBER;
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
    assert (asm_file -> file_buffer);
    free   (asm_file -> file_buffer);
    asm_file -> file_buffer = nullptr;
    
    assert (asm_file -> lexem);
    free (asm_file -> lexem);
    asm_file -> lexem = nullptr;
}              

//=====================================================================================================