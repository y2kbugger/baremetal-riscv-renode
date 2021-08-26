#include <stdint.h>
#include <unistd.h>

#include "process.h"

struct Process PROCESSES[256];

void init_process(struct Process *p, void *function)
{
    p->sp = &(p->stack[PROC_STACK_SIZE - 1]);
    *(p->sp--) = (size_t)function;

    for (size_t i = 28; i > 0; i--)
    {
        *(p->sp--) = 0xdeedbeef;
    }
}

struct Process *lookup_process(unsigned char id)
{
    return &PROCESSES[id];
}

void add_process(unsigned char id, void *function)
{
    struct Process *p = lookup_process(id);
    p->name = id;
    init_process(p, function);
}