#include "cpu.h"

void CPU_construct ()
{   
    FILE* file = fopen ("../txt files/asm_binary", "rb");
    assert (file != nullptr);

    int f_size = file_size () / sizeof (double);
    int n_cmd  = f_size;

    double* temp_buffer = (double*) calloc (f_size, sizeof (double));
    assert (temp_buffer != nullptr);

    fread (temp_buffer, sizeof (double), n_cmd, file);
    f_size /= 2;
    
    double* buffer      = (double*) calloc (f_size, sizeof (double));
    assert (buffer != nullptr);

    //удаляем пробелы 
    for (int i = 0; i < f_size; i++)
    {
        buffer[i] = temp_buffer[i * 2];
    }

    for (int i = 0; i < f_size; i++)
    {
        printf ("[%d]%lg\n", i, *(buffer + i));
    }

    
    fclose (file);
    free   (buffer);
    free   (temp_buffer);
}

//=====================================================================================================

int file_size ()
{
    struct stat information_buffer = {};

    stat   ("../txt files/asm_binary", &information_buffer);
    printf ("Size of \"%s\" is: %ld bytes.\n", "asm_binary", information_buffer.st_size);

    return information_buffer.st_size;
}

//=====================================================================================================

void defining_commands (double* buffer, int n_cmd)
{
    for (int i = 0; i < n_cmd; i++)
    {
        double command = buffer[i];
        switch (command)
        {
        case  constant-expression :
             code 
            break;
        
        default:
            break;
        }
    }
    return;
}

//=====================================================================================================
