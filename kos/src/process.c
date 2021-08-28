#include <stdint.h>
#include <unistd.h>

#include "process.h"

#define MAX_PROCESS_COUNT 10

struct Program PROGRAMS[256];
struct Process PROCESSES[MAX_PROCESS_COUNT];

struct Process *_get_free_proc()
{
    // naive non-reuse implementation
    static int count = 0;
    return &PROCESSES[count++];
}

struct Process *init_process(struct Program *program)
{
    struct Process *proc = _get_free_proc();
    proc->program = program;
    proc->sp = &(proc->stack[PROC_STACK_SIZE - 1]);
    *(proc->sp--) = (size_t)program->function;

    for (size_t i = 28; i > 0; i--)
    {
        *(proc->sp--) = 0xdeedbeef;
    }

    proc->status = Ready;

    return proc;
}

struct Program *lookup_program(unsigned char id)
{
    return &PROGRAMS[id];
}

struct Process *lookup_process(unsigned int id)
{
    return &PROCESSES[id];
}

void register_program(unsigned char id, void (*function)())
{
    struct Program *program = lookup_program(id);
    program->function = function;
    program->name = id;
}

struct Process *next_ready_process(struct Process *current_process)
{
    size_t current_process_idx = current_process - PROCESSES;
    for (size_t i = 1; i <= MAX_PROCESS_COUNT; i++)
    {
        size_t proc_idx = (i + current_process_idx) % MAX_PROCESS_COUNT;
        struct Process *proc = &PROCESSES[proc_idx];
        if (proc->status == Ready)
            return proc;
    }
    return NULL;
}