#include "../baremetal.h"
#include "../uart.h"
#include "../timer.h"
#include "programs.h"

const char SIGSTOP = '\032';
const char SIGKILL = '\003';

void _usage()
{
    puts("Programs:\n");
    puts("    h: hello world\n");
    puts("    e: hello ecall world\n");
    puts("    l: laugh\n");
    puts("    f: laugh forever\n");
    puts("    c: count forever\n");

    puts("Shell commands:\n");
    puts("    ?: show this help\n");
    puts("    @: list stopped processes\n");
    puts("    ^: restart all stopped processes in background\n");
    puts("    !: stop all background processes.\n");
    puts("  C-Z: stop foreground process\n");
    puts("  C-C: kill foreground process\n");
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

void start_stopped_processes()
{
    struct Process *proc = lookup_process(0);
    while ((proc = next_process_of_status(proc, Stopped, false)) != NULL)
        proc->status = Ready;
}

void shell()
{
    while (1)
    {
        puts("\nkos> ");
        char name = getc();
        putc('\n');

        if (name == '\n')
            continue;

        if (name == SIGSTOP)
            continue;

        if (name == SIGKILL)
            continue;

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

        if (name == '^')
        {
            start_stopped_processes();
            continue;
        }

        if (name == '!')
        {
            stop_all_processes_except(current_process);
            continue;
        }

        struct Program *prog = lookup_program(name);
        if (name != prog->name)
        {
            puts("No program `");
            putc(name);
            puts("` registered\n");
            continue;
        }

        struct Process *proc = init_process(prog);
        if (NULL == proc)
        {
            puts("Failed to start `");
            putc(name);
            puts("`\n");
            continue;
        }

        while (proc->status == Ready)
        {
            if (peekc() == SIGKILL)
            {
                getc();
                proc->status = Dead;
            }
            else if (peekc() == SIGSTOP)
            {
                getc();
                proc->status = Stopped;
            }
        }
    }
}
