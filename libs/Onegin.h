#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include <stdio.h>                
#include <stdlib.h>               
#include <string.h>               
#include <sys/stat.h>             
#include <sys/types.h>            
#include <locale.h>               
#include <ctype.h>
#include <assert.h>

//------------------------------------------------------------------------------------------------

struct text 
{
    int   size_of_file;
    int   number_line;
    char* file_buffer;
    int   number_lexems;
    
    struct str*      strings;
    struct lexemes*  lexem;
};
//сделать флаг который будет выбирать структуру по надобности

struct str
{
    char* p_begin_str;
    int   str_length;
};

struct lexemes 
{
    int   lexem_type;
    char* lexem_name;
};

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[]);

char* read_file    (char* file_name, int size_of_file);
int   file_size    (char* file_name);
int  counter_line  (char* file_buffer);
void input_inform  (char* file_name, text* text_info);

void place_pointers (text* text_info);
void free_memory    (text* text_info);
void parsing_lexems (text* text_info);

int skip_spaces   (text* text_info);
int token_counter (text* text_info);


#endif

//------------------------------------------------------------------------------------------------