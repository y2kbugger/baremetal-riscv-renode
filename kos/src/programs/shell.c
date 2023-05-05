#include "../baremetal.h"
#include "../uart.h"
#include "../timer.h"
#include "programs.h"
#include <string.h>

#define SIGSTOP '\032'
#define SIGKILL '\003'
#define SIGSTOP_CMD ((const char[]){SIGSTOP, '\0'})
#define SIGKILL_CMD ((const char[]){SIGKILL, '\0'})

void _usage();
void start_stopped_processes();
void print_stopped_processes();
void try_start_foreground_process(char name);
void run_foreground_process(struct Process *proc);
void stop_all_processes_except_current();

struct command_entry
{
    const char *command;
    void (*function)(void);
};

struct command_entry command_table[] = {
    {"/n", NULL},
    {SIGSTOP_CMD, NULL},
    {SIGKILL_CMD, NULL},
    {"?", _usage},
    {"@", print_stopped_processes},
    {"^", start_stopped_processes},
    {"!", stop_all_processes_except_current},
    {NULL, NULL} // Marks the end of the array
};

static void execute_command(const char *command)
{
    for (int i = 0; command_table[i].command != NULL; i++)
    {
        if (strcmp(command, command_table[i].command) == 0)
        {
            if (command_table[i].function != NULL)
                command_table[i].function();
            return;
        }
    }

    // If no matching command is found, try to start a foreground process
    try_start_foreground_process(command[0]);
}

void shell()
{
    puts("Welcome to the KOS shell!\n");
    puts("Type ? for usage info.\n");
    putc('\n');
    while (1)
    {
        puts("kos> ");
        // just single char commands for now
        char *command = "x";
        command[0] = getc();
        putc('\n');

        execute_command(command);
    }
}

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

void stop_all_processes_except_current()
{
    stop_all_processes_except(current_process);
}
