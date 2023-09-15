#include <string.h>
#include <stdio.h>

#include "../baremetal.h"
#include "../uart.h"
#include "../timer.h"
#include "programs.h"

#define SIGKILL '\003'
#define SIGSTOP '\032'
#define ESCAPE '\033'
#define BACKSP '\010'

bool LOUD_TASK_SWITCHING = false;

void _usage();
void start_stopped_processes();
void print_stopped_processes();
void try_start_foreground_process(char name);
void run_foreground_process(struct Process *proc);
void stop_all_processes_except_current();
char *read_command();

void enable_loud_task_switching()
{
    LOUD_TASK_SWITCHING = true;
}
void disable_loud_task_switching()
{
    LOUD_TASK_SWITCHING = false;
}

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
    {"set loud_switching", enable_loud_task_switching},
    {"unset loud_switching", disable_loud_task_switching},
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
    printf("Welcome to the KOS shell!\n");
    printf("Type ? for usage info.\n\n");
    while (1)
    {
        char *cmd = read_command();
        execute_command(cmd);
    }
}

void _usage()
{
    printf("Programs:\n");
    printf("    h: hello world\n");
    printf("    e: hello ecall world\n");
    printf("    l: laugh\n");
    printf("    f: laugh forever\n");
    printf("    c: count forever\n");
    printf("    v: verilator matrix multiply\n");
    printf("    v: verilator matrix multiply test\n");
    printf("    m: multiply your matrices\n");

    printf("Shell commands:\n");
    printf("    ?: show this help\n");
    printf("    @: list stopped processes\n");
    printf("    ^: restart all stopped processes in background\n");
    printf("    !: stop all background processes.\n");
    printf("  C-Z: stop foreground process\n");
    printf("  C-C: kill foreground process\n");

    printf("Shell Flags:\n");
    printf("set/unset e.g. `set loud_switching`\n");
    printf("Flags:\n");
    printf("  loud_switching: print a * every time shell is switched in during\n");
    printf("                  a the running of a foreground process\n");
}

void print_stopped_processes()
{
    struct Process *proc = lookup_process(0);
    while ((proc = next_process_of_status(proc, Stopped, false)) != NULL)
    {
        printf("  - %c\n", proc->program->name);
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
        printf("No program `%c` registered\n", name);
        return;
    }

    struct Process *proc = init_process(prog);
    if (NULL == proc)
    {
        printf("Failed to start `%c`\n", name);
        return;
    }

    run_foreground_process(proc);
}

void run_foreground_process(struct Process *proc)
{
    while (proc->status == Ready)
    {
        if (LOUD_TASK_SWITCHING)
            _write(1, "*", 1);
        if (!uart_has_data())
        {
            yield_from_this_process();
            continue;
        }
        int c = getchar();
        if (c == SIGKILL)
        {
            proc->status = Dead;
        }
        else if (c == SIGSTOP)
        {
            proc->status = Stopped;
        }
        else
        {
            printf("Forwarding character: `%c` to program `%c`\n", c, proc->program->name);
            ungetc(c, stdin);
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
    struct key_sequence key = {getchar(), NORMAL};
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
    printf("kos> ");
    fflush(stdout);

    while (command_end == command)
        while (1)
        {
            int c = getchar();
            if (c == '\n')
                break;
            if (c == SIGSTOP)
                continue;
            if (c == SIGKILL)
                continue;
            if (c == ESCAPE)
            {
                getchar();
                getchar();
                getchar();
                *command_end++ = 'x';
                *command_end++ = 'x';
                *command_end++ = 'x';
                putchar('x');
                putchar('x');
                putchar('x');
                fflush(stdout);
                continue;
            }

            putchar(c);
            fflush(stdout);
            *command_end++ = c;
        }

    putchar('\n');
    fflush(stdout);

    *command_end = '\0';
    return command;
}
