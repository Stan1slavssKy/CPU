#ifndef COMMANDS_H
#define COMMANDS_H

//=================================================

namespace asm_cmd
{
    enum commands
    {
        PUSH        =  1,
        POP         =  2,
        ADD         =  3,
        SUB         =  4,
        DIV         =  5,
        MUL         =  6,
        OUT         =  7,
        HLT         =  8,
        END         =  9,
        UNKNOWN_CMD = -5
    };
}

//=================================================

enum regs
{
    RAX = 777,
    RBX = 778,
    RCX = 779,
    RDX = 7710
};

//=================================================

enum cmd_flags
{
    REG_CMD = 1,
    NMB_CMD = 0
};

//=================================================

enum lexemes_types
{
    COMMAND   = 1111,
    N_COMMAND = 2222,
    NUMBER    = 3333,
    REGISTER  = 4444,
    LABEL     = 5555
};

//=================================================

#endif 
