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
    
    asm_cmd::firs_passing   (asm_file, label);
    asm_cmd::second_passing (asm_file, label);
}

//=====================================================================================================

void asm_cmd::firs_passing (text* asm_file, labels* label)
{
    assert (asm_file);
    assert (asm_file -> lexem);
    assert (asm_file -> file_buffer);
   
    int flag_counter = 0;  
    int nmb_flags = 0;
    int nmb_lexems   = asm_file -> number_lexems;

    double number    = 0; 
    
    char* cmd = nullptr;

    for (int i = 0; i < nmb_lexems; i++)
    {
        char* lexem = (asm_file -> lexem + i) -> lexem_name;
        int   lex_len = strlen (lexem);
        
        cmd = (asm_file -> lexem + i) -> lexem_name;
       
        if (isdigit (*cmd))
        {
            number = atof (cmd);
            printf ("number is %lg\n", number);
            (asm_file -> lexem + i) -> lexem_type = NUMBER;
        }

        else 
        {
            printf ("cmd is %s\n", cmd);
            (asm_file -> lexem + i) -> lexem_type = COMMAND;

            if (!strcmp (cmd, "push") || !strcmp (cmd, "pop"))
            {
                printf ("\t\t\tCMD is %s\n", cmd);
                nmb_flags = flags_input (asm_file, nmb_lexems, i, nmb_flags);
                printf ("\t\tNUMBER flagsss IS %d\n", nmb_flags);
            }
            if (lexem[lex_len - 1] == ':')
            {
                (asm_file -> lexem + i) -> lexem_type = LABEL;
                lexem[lex_len - 1] = '\0';

                label -> label_name = lexem;
                printf ("\t\tNUMBER FLAGS IS %d\n", nmb_flags);
                label -> ip = i + nmb_flags;
            }
        }
    }
}
    

//=====================================================================================================

// проверяет что стоит после push или pop если регистр ставит флаг REG_COMAND, если число - NMB_COMAND
// возвращает количество флагов
//!!!!!!!!! СДЕЛАТЬ БЕЗАРГУМЕНТОВЫЙ POP

int flags_input (text* asm_file, int nmb_lex, int i, int nmb_flags)
{
    if (i < nmb_lex - 1)
    {
        char* next_lex = (asm_file -> lexem + i + 1) -> lexem_name;

        if (isdigit (*next_lex)) // если след лексема число то это не регистр
            (asm_file -> lexem + i) -> lexem_type = REG_COMMAND;

        else if (*(next_lex) == 'r') //если так то это регистр
        {    
            (asm_file -> lexem + i) -> lexem_type = NMB_COMMAND;
            nmb_flags++;
        }
    }
    
    return nmb_flags;
}

//=====================================================================================================

void asm_cmd::second_passing (text* asm_file, labels* label)
{
    assert (asm_file);
    assert (asm_file -> lexem);
    assert (asm_file -> file_buffer);

    double* byte_code = (double*) calloc (asm_file -> size_of_file, sizeof (double));
    assert (byte_code);

    int nmb_lexems = asm_file -> number_lexems;
    int number = 0;
    
    for (int i = 0; i < nmb_lexems; i++)
    {
        char* lexem_name = (asm_file -> lexem + i) -> lexem_name;
        int   lexem_type = (asm_file -> lexem + i) -> lexem_type;

        if (lexem_type == NUMBER)
        {
            number = atof (lexem_name);
            byte_code [i] = asm_cmd::assembling (asm_file, nullptr, number, asm_file -> lexem + i);
        }

        else 
        {
            if ((asm_file -> lexem + i) -> lexem_type == LABEL)
                continue; 

            byte_code [i] = asm_cmd::assembling (asm_file, lexem_name, 0, asm_file -> lexem + i);
            
            i = placing_flags (asm_file, label, byte_code, nmb_lexems, i);

            if (byte_code[i] == JMP)
                i = label_input (asm_file, label, byte_code, (asm_file -> lexem + i + 1) -> lexem_name, i); 
        }
    }

    input_b_file (asm_file, byte_code);
    free (byte_code);
}

//=====================================================================================================

int placing_flags (text* asm_file, labels* label, double* byte_code, int nmb_lexems, int i)
{
    if (i < nmb_lexems - 1)
    {
        int lex_type = (asm_file -> lexem + i) -> lexem_type;

        if (lex_type == REG_COMMAND) // если след лексема число то это не регистр
        {
            byte_code [++i] = REG_FLAG;
            printf ("flag is %lg\n\n", byte_code [i]);
        }

        else if (lex_type == NMB_COMMAND) // если след лексема число то это не регистр
        {
            byte_code [++i] = NMB_FLAG;
            printf ("flag is %lg\n\n", byte_code [i]);
        }
        //здесь можно еще один иф для без аргументного pop
    }

    return i;
}

//=====================================================================================================

// Проходится по всему массиву структур чтобы найти индекс нашей метки затем кладет в байткод айпи куда джампится

int label_input (text* asm_file, labels* label, double* byte_code, char* next_cmd, int i)
{
    int label_index = 0;
    int nmb_lexems  = asm_file -> number_lexems;

    for (int index = 0; index < nmb_lexems; index++)
    { 
        if (!strcmp(((label + index) -> label_name), next_cmd))
        {
            label_index = (label + index) -> ip - 1;  
            break;
        }
    }

    byte_code [++i] = label_index;

    return i;
}

//=====================================================================================================

double asm_cmd::assembling (text* asm_file, char* cmd, int number, lexemes* lexem_i)
{
    if (cmd != nullptr)
    {
        if (false) {} 

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

    else if (number != 0)             
        return number;                        
    else 
        printf ("\t\tError cmd is {%s}\n\n", cmd);
    
    return -1;
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
