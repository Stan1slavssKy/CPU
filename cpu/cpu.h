#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED 

//===========================================================================

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h> 
#include <sys/stat.h>  
#include <ctype.h>

#include "../libs/Onegin.h"
#include "../libs/protection.h"
#include "../libs/CPU_commands.h"

//===========================================================================


//===========================================================================

struct CPU_t 
{
    Stack_t*   stack;
    double*    byte_code;

    struct Regist*  regs;
    struct cmp_flag* flag;
};

struct Regist
{
    double rax = 0;
    double rbx = 0;
    double rcx = 0;
    double rdx = 0;
};

struct cmp_flag
{
    int ZF = 0;
    int SF = 0;
};

//===========================================================================  

#define ARIFMETICAL_CMD(command, operation)                          \
{                                                                    \
            x1  = stack_pop (cpu -> stack);                          \
            x2  = stack_pop (cpu -> stack);                          \
            res = x2 operation x1;                                   \
                                                                     \
            stack_push (cpu -> stack, res);                          \
            fprintf (cpu_file, "\t\t"#command" %lg %lg\n", x2, x1);  \
            cpu_print (cpu, cpu_file);                               \
}                                                                    \

#define RESET_FLAGS                  \
            (cpu -> flag) -> ZF = 0; \
            (cpu -> flag) -> SF = 0; \

//===========================================================================

void CPU_construct (CPU_t* cpu, char* file_name);
int  CPU_read_file (CPU_t* cpu, char* file_name);
void CPU_destruct  (CPU_t* cpu);
void cpu_print     (CPU_t* cpu, FILE* cpu_file);

namespace asm_cmd
{   
    int determine_commands (CPU_t* cpu, int size_of_file);
}

const char* reg_push (CPU_t* cpu, double reg);
const char* reg_pop  (CPU_t* cpu, double reg);

//===========================================================================

#endif