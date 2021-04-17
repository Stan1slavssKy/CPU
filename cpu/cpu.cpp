#include "cpu.h"

void CPU_construct (CPU_t* cpu, char* file_name)
{   
    stack_constr(stk, 2);
    cpu -> stack = &stk;
    
    CPU_read_file (cpu, file_name);
    asm_c::defining_commands (cpu);

    stack_dump (cpu -> stack);
    stack_destruct (cpu -> stack);
}

//=====================================================================================================

void CPU_read_file (CPU_t* cpu, char* file_name)
{
    assert (cpu);
    assert (cpu -> stack);
    assert (file_name);

    FILE* file = fopen (file_name, "rb");
    assert (file);

    int size_of_file = file_size (file_name);
    
    double* file_buffer  = (double*) calloc (size_of_file, sizeof(double));
    assert (file_buffer);

    cpu -> byte_code = file_buffer;

    fread  (file_buffer, sizeof (char), size_of_file, file);
    fclose (file);

    for (int i = 0; i < size_of_file / 8; i++)
    {
        printf ("[%lg] ", file_buffer [i]);
    }

    printf ("\n");
}

//=====================================================================================================

int asm_c::defining_commands (CPU_t* cpu)
{
    assert (cpu);
    assert (cpu -> stack);
    assert (cpu -> byte_code);
    
    double* buffer = cpu -> byte_code;
    
    double x1  = 0,
           x2  = 0,
           res = 0;

    for (int i = 0; buffer[i] != 0 ; i++)
    {
        double cmd  = buffer [i];

        switch ((int) cmd)
        {
        case PUSH:
            stack_push (cpu -> stack, buffer[++i]);
            print_array (cpu -> stack);
            break;

        case POP:
            res = stack_pop (cpu -> stack);
            printf ("\n\t\tNumber is %lg\n\n", res);
            break;

        case ADD:
            x1  = stack_pop (cpu -> stack);
            x2  = stack_pop (cpu -> stack);
            res = x1 + x2;
            
            stack_push (cpu -> stack, res);
            print_array (cpu -> stack);  
            break;

        case SUB:
            x1  = stack_pop (cpu -> stack);
            x2  = stack_pop (cpu -> stack);
            res = x1 - x2;
            
            stack_push (cpu -> stack, res);
            print_array (cpu -> stack);  
            break;

        case DIV:
            x1  = stack_pop (cpu -> stack);
            x2  = stack_pop (cpu -> stack);
            res = x1 / x2;
            
            stack_push (cpu -> stack, res); 
            print_array (cpu -> stack); 
            break;

        case MUL:
            x1  = stack_pop (cpu -> stack);
            x2  = stack_pop (cpu -> stack);
            res = x1 * x2;
        
            stack_push (cpu -> stack, res); 
            print_array (cpu -> stack); 
            break;
       
        case END:
            return 0;


        default:
            printf ("Error CPU don't know your command:(\n");
            return -1;
        }
    }

    return 0;
}

//=====================================================================================================

void CPU_destruct (CPU_t* cpu)
{
    assert (cpu);
    assert (cpu -> byte_code);

    free (cpu -> byte_code);
}

//=====================================================================================================