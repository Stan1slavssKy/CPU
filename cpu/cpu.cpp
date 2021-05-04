#include "cpu.h"

void CPU_construct (CPU_t* cpu, char* file_name)
{   
    stack_constr(stk, 2);
    cpu -> stack = &stk;    
    cpu -> regs  = (Regist*) calloc (4, sizeof (double));

    int size_of_file = CPU_read_file (cpu, file_name);
    asm_cmd::determine_commands (cpu, size_of_file);

    stack_dump     (cpu -> stack);
    stack_destruct (cpu -> stack);
}

//=====================================================================================================

int CPU_read_file (CPU_t* cpu, char* file_name)
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

    return size_of_file;
}

//=====================================================================================================

int asm_cmd::determine_commands (CPU_t* cpu, int size_of_file)
{
    assert (cpu);
    assert (cpu -> stack);
    assert (cpu -> byte_code);
    
    FILE* cpu_file = fopen ("../txt files/cpu_dump", "wb"); 
    assert (cpu_file);

    double* buffer = cpu -> byte_code;

    cpu -> flag = (cmp_flag*) calloc (2, sizeof (cmp_flag));
    assert (cpu -> flag);

    double x1  = 0;
    double x2  = 0;
    
    double res       = 0;
    double next_code = 0;
    int jmp_idx;
    int nmb_lex = size_of_file / sizeof (double);

    printf ("nmb_lexems = %d\n", nmb_lex);

    for (int i = 0; i < nmb_lex ; i++)
    {
        double cmd = buffer [i];
        switch ((int) cmd)
        {
            case PUSH:
            {
                next_code = buffer [++i];

                if (next_code == 0) // проверка флага на ноль если так то это число
                {
                    stack_push (cpu -> stack, buffer[++i]);
                    fprintf (cpu_file, "\t\tpush %lg:\n", buffer[i]);
                    cpu_print (cpu, cpu_file);
                }
                else if (next_code == 1) // push register
                {
                    const char* reg_name = reg_push (cpu, buffer[++i]);
                    fprintf (cpu_file, "\t\tpush from register %s\n", reg_name);
                    cpu_print (cpu, cpu_file);    
                }
                break;
            }

            case POP:
            {
                next_code = buffer [++i];
                
                if (next_code == 0)
                {
                    res = stack_pop (cpu -> stack);               
                    fprintf (cpu_file, "\n\t\tpop %lg\n", res);
                }
                else if (next_code == 1)
                {
                    const char* reg_name = reg_pop (cpu, buffer[++i]);
                    fprintf (cpu_file, "\t\tpop in register %s\n", reg_name);
                    cpu_print (cpu, cpu_file); 
                }
                break;
            }

            case ADD:
            {
                ARIFMETICAL_CMD(add, +);
                break;
            }

            case SUB:
            {
                ARIFMETICAL_CMD(sub, -);
                break;
            }

            case DIV:
            {
                ARIFMETICAL_CMD(div, /);
                break;
            }

            case MUL:
            {
                ARIFMETICAL_CMD(mul, *);
                break;
            }

            case OUT:
            {
                res = stack_pop (cpu -> stack);

                stack_push (cpu -> stack, res);
                fprintf (cpu_file, "\t\tout: %lg\n", res);
                cpu_print (cpu, cpu_file);
                break; 
            }

            case END:
            {
                fprintf (cpu_file, "\t\tend\n");
                fclose (cpu_file);
                return 0;
            }

            case JMP:
            {
                jmp_idx = (int) buffer[i + 1] - 1; //цикл фор накинет еще 1
                fprintf (cpu_file, "\t\tjump to byte_code[%d] = %lg\n", jmp_idx + 1, buffer[jmp_idx + 1]);
                i = jmp_idx;
                RESET_FLAGS
                break;
            }

            case JE:
            {
                if ((cpu -> flag) -> ZF == 1)
                {
                    jmp_idx = (int) buffer[i + 1] - 1; 
                    fprintf (cpu_file, "\t\tjump to byte_code[%d] = %lg\n", jmp_idx + 1, buffer[jmp_idx + 1]);
                    i = jmp_idx - 1;   
                }
                RESET_FLAGS
                i++;
                break;
            }

            case JNE:
            {
                fprintf (cpu_file, "\t\tline is %d  before if ZF = [%d]\n", __LINE__, (cpu->flag)->ZF);
                if ((cpu -> flag) -> ZF == 0)
                {
                    jmp_idx = (int) buffer[i + 1] - 1; 
                    fprintf (cpu_file, "\t\tjump to byte_code[%d] = %lg\n", jmp_idx + 1, buffer[jmp_idx + 1]);
                    i = jmp_idx - 1;
                }
                RESET_FLAGS
                i++;
          
                break;
            }

            case CMP:
            {
                x1 = stack_pop (cpu -> stack);
                x2 = stack_pop (cpu -> stack);

                if (x1 == x2)
                {
                    (cpu -> flag) -> ZF = 1;
                }
                else 
                {
                    (cpu -> flag) -> ZF = 0;
                }
                fprintf (cpu_file, "\t\tcmp %lg and %lg\n", x2, x1);
                break;
            }
            
            case INC:
            {
                const char* reg_name = reg_push (cpu, buffer[++i]);
                x1 = stack_pop (cpu -> stack);
                x1++;
                stack_push (cpu -> stack, x1);
                reg_pop (cpu, buffer[i]);
                fprintf (cpu_file, "\t\tinc register %s\n", reg_name);
                cpu_print (cpu, cpu_file);
                break;
            }

            case DEC:
            {
                const char* reg_name = reg_push (cpu, buffer[++i]); 
                x1 = stack_pop (cpu -> stack);
                x1--;
                stack_push (cpu -> stack, x1);
                reg_pop (cpu, buffer[i]);
                fprintf (cpu_file, "\t\tdec register %s\n", reg_name);
                cpu_print (cpu, cpu_file);
                break;
            }

            case UNKNOWN_CMD:
            {
                fclose (cpu_file);
                return -1;
            }

            default:
            {
                fprintf (cpu_file, "Error CPU don't know your command:(\n");
                fclose (cpu_file);
                return -2;
            }
        }
    }

    fclose (cpu_file);

    return 0;
}

//=====================================================================================================

const char* reg_push (CPU_t* cpu, double reg)
{
    int number = 0;

    if ((int)reg == RAX)                     
    {                                  
        number = (cpu -> regs) -> rax;
        stack_push (cpu -> stack, number);  
        return "rax";                   
    }  
    else if ((int)reg == RBX)                     
    {                                  
        number = (cpu -> regs) -> rbx;
        stack_push (cpu -> stack, number);  
        return "rbx";                   
    }  
    else if ((int)reg == RCX)                     
    {                                  
        number = (cpu -> regs) -> rcx;
        stack_push (cpu -> stack, number);  
        return "rcx";                   
    }  
    else if ((int)reg == RDX)                     
    {                                  
        number = (cpu -> regs) -> rdx;
        stack_push (cpu -> stack, number);  
        return "rdx";                   
    }  

    return "ERROR IN reg_push";
}

//=====================================================================================================
  
const char* reg_pop (CPU_t* cpu, double reg)
{
    int number = 0;

    if ((int)reg == RAX)                     
    {                                  
        number = stack_pop (cpu -> stack); 
        (cpu -> regs) -> rax = number; 
        return "rax";                   
    }  
    else if ((int)reg == RBX)                     
    {                                  
        number = stack_pop (cpu -> stack); 
        (cpu -> regs) -> rbx = number;  
        return "rbx";                   
    }  
    else if ((int)reg == RCX)                     
    {                                  
        number = stack_pop (cpu -> stack); 
        (cpu -> regs) -> rcx = number;  
        return "rcx";                   
    }  
    else if ((int)reg == RDX)                     
    {                                  
        number = stack_pop (cpu -> stack); 
        (cpu -> regs) -> rdx = number;  
        return "rdx";                   
    }  

    return "ERROR IN reg_pop";
}

//=====================================================================================================
  
void cpu_print (CPU_t* cpu, FILE* cpu_file)
{
    for (int i = 0; i < cpu -> stack -> size; i++) 
        fprintf (cpu_file, "\t\t\t[%d]: %f\n", i, *((cpu -> stack) -> data + i)); 

    printf ("\n");
}

//=====================================================================================================

void CPU_destruct (CPU_t* cpu)
{
    assert (cpu);
    assert (cpu -> byte_code);
    assert (cpu -> regs);
    assert (cpu -> flag);

    free (cpu -> byte_code);
    cpu -> byte_code = nullptr;

    free (cpu -> regs);
    cpu -> regs = nullptr;

    free (cpu -> flag);
    cpu -> flag = nullptr;
}

//=====================================================================================================
