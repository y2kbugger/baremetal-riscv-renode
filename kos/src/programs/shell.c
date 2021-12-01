#include "../baremetal.h"
#include "../uart.h"
#include "../timer.h"
#include "programs.h"

#define SIGSTOP '\032'
#define SIGKILL '\003'

void try_start_foreground_process(char name);
void run_foreground_process(struct Process *proc);

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
    putc('\n');
    while (1)
    {
        puts("kos> ");
        char name = getc();
        putc('\n');

        switch (name)
        {
        case '\n':
        case SIGSTOP:
        case SIGKILL:
            break;
        case '?':
            _usage();
            break;
        case '@':
            print_stopped_processes();
            break;
        case '^':
            start_stopped_processes();
            break;
        case '!':
            stop_all_processes_except(current_process);
            break;
        default:
            try_start_foreground_process(name);
        }
    }
}

void try_start_foreground_process(char name)
{
    struct Program *prog = lookup_program(name);
    if (name != prog->name)
    {
        puts("No program `");
        putc(name);
        puts("` registered\n");
        return;
    }

    struct Process *proc = init_process(prog);
    if (NULL == proc)
    {
        puts("Failed to start `");
        putc(name);
        puts("`\n");
        return;
    }

    run_foreground_process(proc);
}

void run_foreground_process(struct Process *proc)
{
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
