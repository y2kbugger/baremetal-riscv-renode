#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <unistd.h>

#define PROC_STACK_SIZE 200

enum ProcessStatus
{
    Uninitialized,
    Ready,
    Running,
    Dead,
    Stopping,
    Stopped,
};

struct Program
{
    void (*function)();
    unsigned char name;
};

struct Process
{
    size_t *sp;
    struct Program *program;
    enum ProcessStatus status;
    size_t stack[PROC_STACK_SIZE];
};

void register_program(unsigned char id, void (*function)());
struct Program *lookup_program(unsigned char id);
struct Process *init_process(struct Program *p);
struct Process *lookup_process(unsigned int id);
struct Process *next_process_of_status(struct Process *current_process, enum ProcessStatus status);
void stop_all_processes_except(struct Process *excepted_process);

#endif /* PROCESS_H */
