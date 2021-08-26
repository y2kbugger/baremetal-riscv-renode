#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <unistd.h>

#define PROC_STACK_SIZE 200

struct Process
{
    size_t *sp;
    size_t stack[PROC_STACK_SIZE];
    unsigned char name;
};

void add_process(unsigned char id, void *function);
struct Process *lookup_process(unsigned char id);
void init_process(struct Process *p, void *function);

#endif /* PROCESS_H */
