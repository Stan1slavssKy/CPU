#ifndef COMMANDS_H
#define COMMANDS_H

//=================================================

namespace asm_cmd
{
    enum commands
    {
        PUSH        = 1,
        POP         = 2,
        ADD         = 3,
        SUB         = 4,
        DIV         = 5,
        MUL         = 6,
        OUT         = 7,
        HLT         = 8,
        END         = 9,
        JMP         = 10,
        JE          = 11,
        JNE         = 12,
        INC         = 13,
        DEC         = 14,
        CMP         = 15,
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
    REG_FLAG = 1,
    NMB_FLAG = 0
};

//=================================================

enum lexemes_types
{
    COMMAND     = 1111,
    NUMBER      = 3333,
    REGISTER    = 4444,
    LABEL       = 5555,
    REG_COMMAND = 6666,
    NMB_COMMAND = 7777
};

//=================================================

#endif 
