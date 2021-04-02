#include "cpu.h"

void CPU_construct ()
{   
    FILE* file = fopen ("../assembler/asm_binary", "r");
    assert (file != nullptr);

    int f_size = file_size ();
    int n_cmd  = f_size;

    double* buffer = (double*) calloc (f_size, sizeof (double));

    fread (buffer, sizeof (double), n_cmd, file);

    for (int i = 0; i < f_size; i++)
    {
        printf ("[%d]%lg\n", i, *(buffer + i));
    }

   // defining_commands (buffer, n_cmd);
    
    fclose (file);
    free  (buffer);
}

//=====================================================================================================

int file_size ()
{
    const char* file_name = "../CPU/assembler/asm";
    struct stat information_buffer = {};

    stat   (file_name, &information_buffer);
    printf ("Size of \"%s\" is: %ld bytes.\n", file_name, information_buffer.st_size);

    return information_buffer.st_size;
}

//=====================================================================================================

/*void defining_commands (double* buffer, int n_cmd)
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
}*/

//=====================================================================================================