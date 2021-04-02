#include "assembler.h"

//=====================================================================================================

void read_asm (char* file_name, struct file* asm_file)
{
    asm_file -> size_of_file = file_size    (file_name);
    asm_file -> file_buffer  = read_file    (file_name, asm_file -> size_of_file);
    asm_file -> number_line  = counter_line (asm_file -> file_buffer);

   // asm_file -> number_words = fread (asm_buffer, sizeof (char), file_size, file);
}

//=====================================================================================================

int file_size (char* file_name)
{
    struct stat information_buffer = {};

    stat   (file_name, &information_buffer);
    printf ("Size of \"%s\" is: %ld bytes.\n", file_name, information_buffer.st_size);

    return information_buffer.st_size;
}

//=====================================================================================================

char* read_file (char* file_name, int size_of_file)
{
    FILE* file = fopen (file_name, "rb");
    assert (file != NULL);

    char* asm_buffer = (char*) calloc (size_of_file, sizeof(char));
    assert (asm_buffer != NULL);

    fread  (asm_buffer, sizeof (char), size_of_file, file);
    fclose (file);

    return asm_buffer;
}

//=====================================================================================================

int counter_line (char* file_buffer)
{
    char* beg_line   = file_buffer;
    char* end_line   = NULL;
    int line_counter = 0;

    while ((end_line = strchr (beg_line, '\n')) != NULL)
    {
        beg_line = end_line + 1;
        line_counter++;
    }

    printf ("The number of rows is %d\n", line_counter);

    return line_counter;
}

//=====================================================================================================

struct string* place_pointers (struct file* asm_file)
{
    struct string* data = (struct string*) calloc (asm_file -> number_line, sizeof (struct string)); // массив указателей на структуры

    char* p_beg_str = (asm_file -> file_buffer);
    char* p_end_str = NULL;

    for (int i = 0; i < (asm_file -> number_line); i++)
    {
        p_end_str = strchr (p_beg_str, '\n');

        if (p_end_str != NULL) 
            *p_end_str = '\0';
        else
            p_end_str = strchr (p_beg_str, '\0') + 1; 

        (data + i) -> beg_ptr     = p_beg_str;
        (data + i) -> str_length  = p_end_str - p_beg_str;

        printf ("%d\n", (data + i) -> str_length);
        p_beg_str = p_end_str + 1;
    }

    return data;
}

//=====================================================================================================
