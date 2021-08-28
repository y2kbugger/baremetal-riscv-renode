#include "../baremetal.h"
#include "../uart.h"
#include "programs.h"

void shell()
{
    while (1)
    {
        puts("Programs:\n");
        puts(" h: hello world\n");
        puts(" l: laugh\n");
        puts(" f: laugh forever\n");
        puts(" c: count forever\n");
        puts("Launch one or more programs by submitting characters.\n");
        // puts("! will stop the currently running process.\n");
        // puts("An empty return will list info about currently running processes.\n");
        puts("kos> ");

        char name;
        while ((name = getc()) == '\n')
            ;

        if (name == '!')
        {
            // handling stopping a process here
            // last_process->status = Stopping;
            continue;
        }

        if (NULL == init_process(lookup_program(name)))
        {
            puts("Failed to start ");
            putc(name);
            putc('\n');
        }
    }
}
