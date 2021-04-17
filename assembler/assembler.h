#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h> 
#include <sys/stat.h>  
#include <ctype.h>

#include "../libs/Onegin.h"
#include "../libs/CPU_commands.h"

//=================================================================================

enum lexsemes_names
{
    COMMAND   = 1111,
    N_COMMAND = 2222,
    NUMBER    = 3333,
    REGISTER  = 4444,
    LABEL     = 5555
};

//=================================================================================

struct lexsemes 
{
    int   lexsem_type = 0;
    char* lexsem_name = nullptr;
};

//=================================================================================

#define GET_COMMAND(cmd_compared, CMD_ENUM, number)      \
    else if (!strcmp(cmd, #cmd_compared))                \
    {                                                    \
        checking_lex_type (cmd_lexem, CMD_ENUM, number); \
        return CMD_ENUM;                                 \
    }


#define TYPE_COMMAND(CMD_ENUM, LEX_TYPE)     \
    case CMD_ENUM:                           \
        cmd_lexem -> lexsem_type = LEX_TYPE; \
        break;

//=================================================================================

void assembler_read (text* asm_file, char* file_name);
void assembler_free (text* asm_file);

void read_asm         (char* file_name, text* asm_file);
void asm_file_analize (text* asm_file, lexsemes* cmd_lexem);
void input_b_file     (text* asm_file, double* byte_code);

namespace asm_c
{
    double assembling (lexsemes* cmd_lexem, char* cmd, int number);
    void checking_lex_type (lexsemes* cmd_lexem, int CMD_ENUM, int number);
}

int    create_byte_code (text* asm_file, int cmd_len, int cmd_code, int cmd_number, int i, int idx_b_code, char* nmb_ptr, double* byte_code); 
char** check_lexemes    (text* asm_file, int i);

//=================================================================================

#endif