#include "cpu.h"

void CPU_construct (CPU_t* cpu, char* file_name)
{   
    stack_constr(stk, 2);
    cpu -> stack = &stk;
    
    CPU_read_file (cpu, file_name);
    asm_cmd::determine_commands (cpu);

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
}

//=====================================================================================================

int asm_cmd::determine_commands (CPU_t* cpu)
{
    assert (cpu);
    assert (cpu -> stack);
    assert (cpu -> byte_code);
    
    FILE* cpu_file = fopen ("../txt files/cpu_dump", "wb"); 
    assert (cpu_file);

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
            fprintf (cpu_file, "\t\tpush %lg:\n", buffer[i]);
            cpu_print (cpu, cpu_file);
            break;

        case POP:
            res = stack_pop (cpu -> stack);
            fprintf (cpu_file, "\n\t\tpop %lg\n", res);
            break;

        case ADD:
            x1  = stack_pop (cpu -> stack);
            x2  = stack_pop (cpu -> stack);
            res = x1 + x2;
            
            stack_push (cpu -> stack, res);
            fprintf (cpu_file, "\t\tadd %lg %lg:\n", x2, x1);
            cpu_print (cpu, cpu_file); 
            break;

        case SUB:
            x1  = stack_pop (cpu -> stack);
            x2  = stack_pop (cpu -> stack);
            res = x2 - x1;
            
            stack_push (cpu -> stack, res);
            fprintf (cpu_file, "\t\tsub %lg %lg\n", x2, x1);
            cpu_print (cpu, cpu_file); 
            break;

        case DIV:
            x1  = stack_pop (cpu -> stack);
            x2  = stack_pop (cpu -> stack);
            res = x2 / x1;
            
            stack_push (cpu -> stack, res); 
            fprintf (cpu_file, "\t\tdiv %lg %lg\n", x2, x1);
            cpu_print (cpu, cpu_file);
            break;

        case MUL:
            x1  = stack_pop (cpu -> stack);
            x2  = stack_pop (cpu -> stack);
            res = x1 * x2;
        
            stack_push (cpu -> stack, res); 
            fprintf (cpu_file, "\t\tmul %lg %lg\n", x2, x1);
            cpu_print (cpu, cpu_file);
            break;

        case OUT:
            res = stack_pop (cpu -> stack);

            stack_push (cpu -> stack, res);
            fprintf (cpu_file, "\t\tout %lg\n", res);
            cpu_print (cpu, cpu_file);
            break; 

        case END:
            return 0;

        case UNKNOWN_CMD:
            return -1;

        default:
            fprintf (cpu_file, "Error CPU don't know your command:(\n");
            return -2;
        }
    }

    fclose (cpu_file);

    return 0;
}

//=====================================================================================================

void CPU_destruct (CPU_t* cpu)
{
    assert (cpu);
    assert (cpu -> byte_code);

    free (cpu -> byte_code);
    cpu -> byte_code = nullptr;
}

//=====================================================================================================

void cpu_print (CPU_t* cpu, FILE* cpu_file)
{
    for (int i = 0; i < cpu -> stack -> size; i++) 
        fprintf (cpu_file, "\t\t[%d]: %f\n", i, *((cpu -> stack) -> data + i)); 

    printf ("\n");
}

//=====================================================================================================