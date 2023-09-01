#include <string.h>

#include "../baremetal.h"
#include "../uart.h"
#include "../timer.h"
#include "programs.h"

#define SIGKILL '\003'
#define SIGSTOP '\032'
#define ESCAPE '\033'
#define BACKSP '\010'
// #define SIGSTOP_CMD ((const char[]){SIGSTOP, '\0'})
// #define SIGKILL_CMD ((const char[]){SIGKILL, '\0'})

void _usage();
void start_stopped_processes();
void print_stopped_processes();
void try_start_foreground_process(char name);
void run_foreground_process(struct Process *proc);
void stop_all_processes_except_current();
char *read_command();
void yell();

struct command_entry
{
    const char *command;
    void (*function)(void);
};

struct command_entry command_table[] = {
    {"?", _usage},
    {"@", print_stopped_processes},
    {"^", start_stopped_processes},
    {"!", stop_all_processes_except_current},
    {"yell", yell},
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
        char *cmd = read_command();
        execute_command(cmd);
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
    puts("    v: verilator matrix multiply\n");

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
enum KEY_TYPE
{
    NORMAL,
    ESCAPE_SEQUENCE,
    CONTROL,
    UNKNOWN,
};

struct key_sequence
{
    char value;
    enum KEY_TYPE type;
};

#define SIGKILL '\003'
#define SIGSTOP '\032'
#define KEY_ESC '\033' // escape
#define KEY_BS '\010'  // backspace
#define KEY_BEL '\007' // bell
struct key_sequence read_key_sequence()
{
    struct key_sequence key = {getc(), NORMAL};
    switch (key.value)
    {
    case SIGKILL:
    case SIGSTOP:
    case BACKSP:
    case '\n':
    case '\r':
    case '\t':
        key.type = CONTROL;
        break;
    }
    return key;
}

char command_buffer[1024];
char *command = command_buffer;
char *read_command()
{
    char *command_end = command;
    puts("kos> ");

    while (command_end == command)
        while (1)
        {
            char c = getc();
            if (c == '\n')
                break;
            if (c == SIGSTOP)
                continue;
            if (c == SIGKILL)
                continue;
            if (c == ESCAPE)
            {
                getc();
                getc();
                getc();
                *command_end++ = 'x';
                *command_end++ = 'x';
                *command_end++ = 'x';
                putc('x');
                putc('x');
                putc('x');
                continue;
            }

            putc(c);
            *command_end++ = c;
        }

    putc('\n');

    *command_end = '\0';
    return command;
}

void yell()
{
    puts("YELL!\n");
}
