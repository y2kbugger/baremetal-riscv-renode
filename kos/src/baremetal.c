#include <stdint.h>
#include <unistd.h>

#include "baremetal.h"
#include "uart.h"
#include "timer.h"
#include "process.h"
#include "programs/programs.h"

struct Process *current_process;
struct Process *next_process;

void init_kernel()
{
    init_uart();
    register_all_programs();
    current_process = init_process(lookup_program('s'));
    init_timer();
    asm volatile("ecall");
}

void schedule_processes()
{
    if (next_process == NULL)
        next_process = next_process_of_status(current_process, Ready);

    if (next_process == NULL)
        return;

    if (current_process->status == Running)
        current_process->status = Ready;

    if (current_process->status == Stopping)
        current_process->status = Stopped;

    current_process = next_process;
    current_process->status = Running;
    next_process = NULL;
}

void end_this_process()
{
    current_process->status = Dead;
    asm volatile("ecall");
}
