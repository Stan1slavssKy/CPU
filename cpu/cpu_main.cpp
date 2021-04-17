#include "cpu.h"

int main (int argc, char* argv[])
{
    CPU_t cpu = {};

    char*   file_name = console_input (argc, argv);
    assert (file_name);

    CPU_construct (&cpu, file_name);
    CPU_destruct  (&cpu);

    return 0;
}