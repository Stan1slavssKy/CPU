#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h> 
#include <sys/stat.h>  
#include <ctype.h>

void CPU_construct ();
int  file_size ();
void defining_commands (double* buffer, int n_cmd);

#endif