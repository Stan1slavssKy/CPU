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
};

struct Regist
{
    int rax = 0;
    int rbx = 0;
    int rcx = 0;
    int rdx = 0;
};

//===========================================================================

void CPU_construct (CPU_t* cpu, char* file_name);
void CPU_read_file (CPU_t* cpu, char* file_name);
void CPU_destruct  (CPU_t* cpu);
void cpu_print     (CPU_t* cpu, FILE* cpu_file);

namespace asm_cmd
{   
    int determine_commands (CPU_t* cpu);
}

const char* reg_push (CPU_t* cpu, double reg);
const char* reg_pop  (CPU_t* cpu, double reg);

//===========================================================================

#endif