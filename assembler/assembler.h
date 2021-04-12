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

//=================================================================================

namespace my_commands
{
    enum commands
    {
        PUSH = 1,
        POP  = 2,
        ADD  = 3,
        SUB  = 4,
        DIV  = 5,
        OUT  = 6,
        HLT  = 7,
        END  = 8,
        UNKNOWN_CMD = 9
    };
}

enum lexsemes_types
{
    COMMAND  = 1,
    NUMBER   = 2,
    REGISTER = 3,
    LABEL    = 4
};

//=================================================================================

struct lexsemes 
{
    int   lexsem_name;
    char* lexsem;
};

//=================================================================================

#define MAX_CMD 4

#define GET_COMMAND(cmd_compared, CMD_ENUM)       \
    else if (!strcmp(cmd, #cmd_compared))         \
        return CMD_ENUM;

//=================================================================================

void assembler_read (text* asm_file, char* file_name);
void assembler_free (text* asm_file);

void    read_asm     (char* file_name, text* asm_file);
void asm_file_analize (text* asm_file, int nmb_spaces);
void    input_b_file (text* asm_file, double* byte_code);
double  assembling   (char* cmd);
int create_byte_code (text* asm_file, int cmd_len, int cmd_code, int cmd_number, int i, int idx_b_code, char* nmb_ptr, double* byte_code); 
char** check_lexemes (text* asm_file, int i);

//=================================================================================

#endif