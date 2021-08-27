#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <unistd.h>

#define PROC_STACK_SIZE 200

struct Program
{
    void (*function)();
    unsigned char name;
};

struct Process
{
    size_t *sp;
    struct Program *program;
    size_t stack[PROC_STACK_SIZE];
};

void register_program(unsigned char id, void (*function)());
struct Program *lookup_program(unsigned char id);
struct Process *lookup_process(unsigned int id);
struct Process *init_process(struct Program *p);

#endif /* PROCESS_H */
