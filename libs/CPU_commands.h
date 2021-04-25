#ifndef COMMANDS_H
#define COMMANDS_H

//=================================================

namespace asm_cmd
{
    enum commands
    {
        PUSH = 1,
        POP  = 2,
        ADD  = 3,
        SUB  = 4,
        DIV  = 5,
        MUL  = 6,
        OUT  = 7,
        HLT  = 8,
        END  = 9,
        UNKNOWN_CMD = -5
    };
}

//=================================================

#endif 