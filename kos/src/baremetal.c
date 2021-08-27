#include <stdint.h>
#include <unistd.h>

#include "baremetal.h"
#include "uart.h"
#include "timer.h"
#include "process.h"
#include "programs/programs.h"

volatile struct Process *current_process;
volatile struct Process *next_process;

void init_kernel()
{
    init_uart();
    init_timer();
    register_all_programs();
    current_process = init_process(lookup_program('m'));
    asm volatile("ecall");
}

void schedule_processes()
{
    if (next_process != NULL)
    {
        current_process = next_process;
        next_process = NULL;
    }
}

void end_this_process()
{
    next_process = lookup_process(0); // monitor
    asm volatile("ecall");
}
