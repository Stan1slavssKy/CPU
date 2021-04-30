#include "assembler.h"

void assembler_read (text* asm_file, char* file_name)
{
    assert (file_name);
    assert (asm_file);

    input_inform (file_name, asm_file);
        
    parsing_lexems (asm_file);
    assert (asm_file -> lexem);
    
    labels* label = (labels*) calloc (asm_file -> number_lexems, sizeof (label));
    assert (label);
    
    checking_label_ip (asm_file, label);
    asm_cmd::asm_file_analize (asm_file, label);
}

//=====================================================================================================

void asm_cmd::asm_file_analize (text* asm_file, labels* label) 
{
    assert (asm_file);
    assert (asm_file -> lexem);
    assert (asm_file -> file_buffer);
   
    char*   cmd      = nullptr;
    double  nmb      = 0;
    
    double* byte_code = (double*) calloc (asm_file -> size_of_file, sizeof (double));
    assert (byte_code);
    
    int nmb_lex      = asm_file -> number_lexems;
    int idx          = 0;
    int flag_counter = 0;

    printf ("nmb lex is %d\n\n", nmb_lex); 

    for (int i = 0; i < nmb_lex; i++)
    {
        cmd = (asm_file -> lexem + i) -> lexem_name;
       
        if (isdigit (*cmd))
        {
            nmb = atof (cmd);
            printf ("nmb is %lg\n", nmb);
            byte_code [idx++] = asm_cmd::assembling (asm_file, nullptr, nmb, asm_file -> lexem + i);
        }

        else
        {  
            printf ("cmd is %s\n", cmd);
            
            if ((asm_file -> lexem + i) -> lexem_type == LABEL)
                continue; 

            byte_code [idx++] = asm_cmd::assembling (asm_file, cmd, 0, asm_file -> lexem + i);

            if (byte_code[idx - 1] == JMP)
            {
                idx = label_input (asm_file, label, (asm_file -> lexem + i + 1) -> lexem_name, byte_code, idx, flag_counter);
                (asm_file -> lexem + i + 1) -> lexem_type = LABEL; 
            }

            int temp = idx;
            idx = flags_input (asm_file, nmb_lex, byte_code, idx, i); //ставим флаг после кманды с регистром
            if (idx != temp) flag_counter++;
        } 
    }

    input_b_file (asm_file, byte_code);
    free (byte_code);
} 

//=====================================================================================================

int flags_input (text* asm_file, int nmb_lex, double* byte_code, int idx, int i)
{
    if (i < nmb_lex - 1)
    {
        char* next_lex = (asm_file -> lexem + i + 1) -> lexem_name;
        double temp    = byte_code [idx];

        if (isdigit (*next_lex)) // если след лексема число то это не регистр
        {
            byte_code [idx++] = NMB_CMD;
            printf ("flag is %lg\n\n", byte_code [idx]);
        }

        else if (*(next_lex) == 'r') //если так то это регистр
        {
            byte_code [idx++] = REG_CMD;
            printf ("reg flag is %lg\n\n", byte_code [idx]);      
        }
    }

    return idx;
}

//=====================================================================================================

int label_input (text* asm_file, labels* label, char* next_cmd, double* byte_code, int idx, int flag_counter)
{
    int label_index = 0;

    for (int index = 0; index < asm_file -> number_lexems; index++)
    { 
        if (!strcmp(((label + index) -> label_name), next_cmd))
        {
            label_index = (label + index) -> ip - 1;  
            break;
        }
    }

    byte_code[idx + flag_counter] = label_index;
    idx++;
    
    return idx;
}

//=====================================================================================================

void checking_label_ip (text* asm_file, labels* label)
{
    assert (asm_file);
    assert (asm_file -> file_buffer);
    assert (asm_file -> lexem);

    for (int i = 0; i < asm_file -> number_lexems; i++)
    {
        char* lexem = (asm_file -> lexem + i) -> lexem_name;
        int   lex_len = strlen (lexem);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1 МОЖНО ПОПРОБОВАТЬ СДЕЛАТЬ СДЕСЬ КАУНТЕР РЕГИСТРОВ ОТ ДЖАМПА ДО САМОЙ МЕТКИ
        if (lexem[lex_len - 1] == ':')
        {
            (asm_file -> lexem + i) -> lexem_type = LABEL;
            lexem[lex_len - 1] = '\0';

            label -> label_name = lexem;
            label -> ip = i;//1111111111111111111111111111
        }
    }
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
        GET_COMMAND (rax, RAX, 0)
        GET_COMMAND (rbx, RBX, 0)
        GET_COMMAND (rcx, RCX, 0)
        GET_COMMAND (rdx, RDX, 0)
        GET_COMMAND (jmp, JMP, 0)
        GET_COMMAND (unknown_cmd, UNKNOWN_CMD, 0)
    }

    else 
    {                                                    
        checking_lex_type (asm_file, NUMBER, number, lexem_i);    
        return number;                        
    } 
    
    printf ("\t\tError cmd is {%s}\n\n", cmd);
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
            TYPE_COMMAND (RAX,   REGISTER)
            TYPE_COMMAND (RBX,   REGISTER)
            TYPE_COMMAND (RCX,   REGISTER)
            TYPE_COMMAND (RDX,   REGISTER)
            TYPE_COMMAND (JMP,   COMMAND)

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
