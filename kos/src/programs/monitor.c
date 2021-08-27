#include "../baremetal.h"
#include "../uart.h"
#include "programs.h"

void monitor()
{
    while (1)
    {
        puts("Programs:\n");
        puts(" h: hello world\n");
        puts(" l: laugh\n");
        puts(" f: laugh forever\n");
        puts("Choose a program to start: ");

        char name;
        while ((name = getc()) == '\n')
            ;

        struct Program *program = lookup_program(name);
        struct Process *proc = init_process(program);
        next_process = proc;
    }
}
