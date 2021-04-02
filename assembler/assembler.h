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

struct file
{
    int size_of_file;
    int number_words;
    int number_line;
    
    char* file_buffer;
};

struct string 
{
    char* beg_ptr;
    int   str_length;
};

struct assembler
{
    
};

//=================================================================================

string* assembler_construct (file* asm_file, char* file_name);
void    assembler_destruct  (char* asm_buffer, string* data);

void   read_asm     (char* file_name, file* asm_file);
char*  read_file    (char* file_name, int size_of_file);
int    file_size    (char* file_name);
int    counter_line (char* file_buffer);

string* place_pointers (file* asm_file);

void   deep_analize_array (file* asm_file, string* data);
void   input_b_file (file* asm_file, char* tokes_arr);
int    assembling   (char* cmd);

#endif