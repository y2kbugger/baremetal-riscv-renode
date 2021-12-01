#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "process.h"

#define MAX_PROCESS_COUNT 10

struct Program PROGRAMS[256];
struct Process PROCESSES[MAX_PROCESS_COUNT];

struct Process *_get_free_proc()
{
    // naive non-reuse implementation
    static int count = 0;
    if (count >= MAX_PROCESS_COUNT)
        return NULL;
    return &PROCESSES[count++];
}

struct Process *init_process(struct Program *program)
{
    struct Process *proc = _get_free_proc();

    if (proc == NULL)
        return NULL;

    proc->program = program;
    proc->sp = &(proc->stack[PROC_STACK_SIZE - 1]);

    const unsigned int ALIGNMENT = 16;
    proc->sp -= ALIGNMENT - ((size_t)proc->sp % ALIGNMENT);

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

// Return the next Process matching a given status.
// If only current_process matches, return it.
// If no Process matches, return NULL.
// Pass status=-1 to match all initialized Process
//
// Use wrap=true to find the next process when traversing from an arbitray point.
// Use wrap=false when traversing from start to end.
// e.g.
//
//    struct Process *proc = lookup_process(0);
//    while ((proc = next_process_of_status(proc, Stopped, false)) != NULL)
struct Process *next_process_of_status(struct Process *current_process, enum ProcessStatus status, bool wrap)
{
    size_t current_process_idx = current_process - PROCESSES;
    for (size_t i = 1; i <= MAX_PROCESS_COUNT; i++)
    {
        size_t proc_idx = (i + current_process_idx) % MAX_PROCESS_COUNT;
        if ((proc_idx <= current_process_idx) && !wrap)
            return NULL;

        struct Process *proc = &PROCESSES[proc_idx];

        if (status == (enum ProcessStatus)(-1) && proc->status != Uninitialized)
            return proc;

        if (proc->status == status)
            return proc;
    }
    return NULL;
}

void stop_all_processes_except(struct Process *excepted_process)
{
    for (size_t i = 0; i < MAX_PROCESS_COUNT; i++)
    {
        struct Process *proc = &PROCESSES[i];
        if (proc == excepted_process)
            continue;
        if (proc->status == Ready)
            proc->status = Stopped;
    }
}
