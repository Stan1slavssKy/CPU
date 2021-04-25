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
        checking_lex_type (asm_file, CMD_ENUM, number, lexem_i) ; \
        return CMD_ENUM;                                          \
    }


#define TYPE_COMMAND(CMD_ENUM, LEX_TYPE)     \
    case CMD_ENUM:                           \
        lexem_i -> lexem_type = LEX_TYPE;    \
        break;

//=================================================================================

void assembler_read (text* asm_file, char* file_name);
void assembler_free (text* asm_file);

void read_asm         (char* file_name, text* asm_file);
void asm_file_analize (text* asm_file);
void input_b_file     (text* asm_file, double* byte_code);

namespace asm_cmd
{
    double assembling      (text* asm_file, char* cmd,    int number, lexemes* lexem_i);
    void checking_lex_type (text* asm_file, int CMD_ENUM, int number, lexemes* lexem_i);
}

int    create_byte_code (text* asm_file, int cmd_len, int cmd_code, int cmd_number, int i, int idx_b_code, char* nmb_ptr, double* byte_code); 
char** check_lexemes    (text* asm_file, int i);

//=================================================================================

#endif