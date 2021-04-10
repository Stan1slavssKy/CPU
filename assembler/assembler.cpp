#include "assembler.h"

void assembler_read (text* asm_file, char* file_name)
{
    input_inform (file_name, asm_file);
   
    place_pointers   (asm_file);
    asm_file_analize (asm_file);
}

//=====================================================================================================
     
void asm_file_analize (text* asm_file)
{
    double   cmd_number = 0; 
    double   cmd_code   = 0;
    int      cmd_len    = 0;

    char* p_beg_str = nullptr;
    char* cmd_ptr   = nullptr;
    char* nmb_ptr   = nullptr;  
    
    double* byte_code = (double*) calloc (asm_file -> size_of_file, sizeof (double)); 
    assert (byte_code);

    int  idx_b_code = 0;

    for (int i = 0; i < (asm_file -> number_line); i++)     // цикл по каждой структуре массива структур
    {
        p_beg_str = (asm_file -> strings + i) -> p_begin_str;
      
        char** lexemes_ptr = check_lexemes (asm_file, i);

        cmd_ptr   = lexemes_ptr[0];
        nmb_ptr   = lexemes_ptr[1];

        if (nmb_ptr != nullptr) /* if found a number*/
        {
            cmd_len     = nmb_ptr - cmd_ptr - 1;
            cmd_number  = atof (nmb_ptr);

            idx_b_code = create_byte_code (asm_file, cmd_len, cmd_code, cmd_number, i, idx_b_code, nmb_ptr, byte_code);     
        }

        else
        {            
            cmd_len = (asm_file -> strings + i) -> str_length;
            idx_b_code = create_byte_code (asm_file, cmd_len, cmd_code, cmd_number, i, idx_b_code, nmb_ptr, byte_code);     
        }

        free (lexemes_ptr);
    }

    input_b_file (asm_file, byte_code);
    
    free (byte_code);
    byte_code = nullptr;
}

//=====================================================================================================

int create_byte_code (text* asm_file, int cmd_len, int cmd_code, int cmd_number, int i, int idx_b_code, char* nmb_ptr, double* byte_code)
{     
    assert (asm_file);  
    assert (byte_code);

    char* p_beg_str = (asm_file -> strings + i) -> p_begin_str;
    assert (p_beg_str);

    char* cmd_buffer  = (char*) calloc (cmd_len + 1, sizeof (char)); // +1 for place /0 cause scrmp need /0
    assert (cmd_buffer);

    for (int item = 0; item < cmd_len; item++) 
        cmd_buffer[item] = p_beg_str[item];
            
    cmd_buffer[cmd_len] = '\0';

    cmd_code = assembling (cmd_buffer);

    free (cmd_buffer);
    cmd_buffer = nullptr;

    byte_code[idx_b_code] = cmd_code;
        idx_b_code++;

    if (nmb_ptr != nullptr)
    {
        byte_code[idx_b_code] = cmd_number;
            idx_b_code++;
    }

    return idx_b_code;
}

//=====================================================================================================

char** check_lexemes (text* asm_file, int i)
{
    char** lexemes_ptr = (char**) calloc (MAX_CMD, sizeof (char*));
    char*  p_beg_str   = (asm_file -> strings + i) -> p_begin_str;

    lexemes_ptr [0] = strtok (p_beg_str, " \n\0");
   
    for (int i = 1; i < MAX_CMD; i++)
    {
        lexemes_ptr [i] = strtok (nullptr, " \n\0");
    }
    
    return lexemes_ptr;
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

    for (int i = 0; i < asm_file -> size_of_file; i++)
    {
        printf ("[%lg]\n", *(byte_code + i));
    }
   
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
