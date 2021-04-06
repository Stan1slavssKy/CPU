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

#include "../../Onegin/Onegin.h"

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

//=================================================================================

#define get_command(cmd_compared, CMD_ENUM)       \
    else if (!strcmp(cmd, #cmd_compared))         \
        return CMD_ENUM;

//=================================================================================

str* assembler_read (file* asm_file, char* file_name);
void assembler_free (char* asm_buffer, str* data);

void    read_asm     (char* file_name, file* asm_file);
void    deep_analize_array (file* asm_file, str* data);
void    input_b_file (file* asm_file, double* tokes_arr);
double  assembling   (char* cmd);

//=================================================================================

#endif