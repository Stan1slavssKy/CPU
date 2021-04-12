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

    struct str*   strings;
};
//сделать флаг который будет выбирать структуру по надобности

struct str
{
    char* p_begin_str;
    int   str_length;
};

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[]);

char* read_file (char* file_name, int size_of_file);

int counter_line (char* file_buffer);
int file_size      (char* file_name);

int direct_comparator  (const void* data1, const void* data2);
int reverse_comparator (const void* data1, const void* data2);
void swap_pointers     (struct str* data1, struct str* data2);

void lexemes_parsing  (struct text* text_info);
void place_pointers   (struct text* text_info);
void free_memory      (struct text* text_info);
void bubble_sort      (struct text* text_info);
void quick_sort       (struct text* text_info);
void output           (struct text* text_info);
void lexemes_counting (struct text* text_info, int index);
void print_text       (struct text* text_info, FILE* finish_file);

void input_inform  (char* file_name, struct text* text_info);
int skip_spaces (text* text_info);

#endif

//------------------------------------------------------------------------------------------------