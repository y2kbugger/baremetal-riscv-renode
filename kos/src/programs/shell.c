#include "../baremetal.h"
#include "../uart.h"
#include "../timer.h"
#include "programs.h"

void _usage()
{
    puts("Programs:\n");
    puts("    h: hello world\n");
    puts("    l: laugh\n");
    puts("    f: laugh forever\n");
    puts("    c: count forever\n");

    puts("Shell commands:\n");
    puts("    ?: show this help\n");
    puts("    @: list stopped processes\n");
    // puts("    ^: restart all stopped processes in background\n");
    puts("    !: stop all processes. This can be used while program\n\tis running in foreground or at prompt to kill any background processes.\n");
}

void print_stopped_processes()
{
    struct Process *proc = lookup_process(0);
    while ((proc = next_process_of_status(proc, Stopped, false)) != NULL)
    {
        puts("  - ");
        putc(proc->program->name);
        putc('\n');
    }
}
void shell()
{
    while (1)
    {
        puts("kos> ");

        char name;
        while ((name = getc()) == '\n')
            ;
        putc('\n');

        if (name == '?')
        {
            _usage();
            continue;
        }

        if (name == '@')
        {
            print_stopped_processes();
            continue;
        }

        struct Process *proc;
        if (NULL == (proc = init_process(lookup_program(name))))
        {
            puts("Failed to start ");
            putc(name);
            putc('\n');
        }

        while (proc->status == Ready && peekc() != '!')
            ;

        if (peekc() == '!')
        {
            getc();
            putc('\n');
            stop_all_processes_except(current_process);
        }
    }
}
