#include "../baremetal.h"
#include "../uart.h"
#include "processes.h"

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

        struct Process *p = lookup_process(name);
        reset_process(p);
        next_process = p;
    }
}
