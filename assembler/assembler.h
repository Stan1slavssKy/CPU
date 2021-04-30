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

#define GET_COMMAND(cmd_compared, CMD_ENUM, number)               \
    else if (!strcmp(cmd, #cmd_compared))                         \
    {                                                             \
        return CMD_ENUM;                                          \
    }


#define TYPE_COMMAND(CMD_ENUM, LEX_TYPE)     \
    case CMD_ENUM:                           \
        lexem_i -> lexem_type = LEX_TYPE;    \
        break;

//=================================================================================

struct labels
{
    char* label_name = nullptr;
    int ip;
};

//=================================================================================

int flags_input    (text* asm_file, int nmb_lex, int i, int nmb_flags);
int  placing_flags (text* asm_file, labels* label, double* byte_code, int nmb_lexems, int i);
int  label_input   (text* asm_file, labels* label, double* byte_code, char* next_cmd, int i);

void assembler_read (text* asm_file, char* file_name);
void input_b_file   (text* asm_file, double* byte_code);
void assembler_free (text* asm_file);

namespace asm_cmd
{
    void   firs_passing   (text* asm_file, labels* label);
    void   second_passing (text* asm_file, labels* label);
    double assembling     (text* asm_file, char* cmd, int number, lexemes* lexem_i);

}

//=================================================================================

#endif
