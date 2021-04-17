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

struct CPU_t 
{
    Stack_t* stack;
    double*  byte_code;
};

//===========================================================================

void CPU_construct (CPU_t* cpu, char* file_name);
void CPU_read_file (CPU_t* cpu, char* file_name);
void CPU_destruct (CPU_t* cpu);

namespace asm_c
{   
    int defining_commands (CPU_t* cpu);
}

//===========================================================================

#endif