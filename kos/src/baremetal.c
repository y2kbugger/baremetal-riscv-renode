#include <stdint.h>
#include <unistd.h>

#include "baremetal.h"
#include "uart.h"
#include "timer.h"
#include "process.h"
#include "processes/processes.h"

volatile struct Process *current_process;
volatile struct Process *next_process;

void init_kernel()
{
    init_uart();
    init_timer();
    init_all_processes();
    current_process = lookup_process('m');
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
    struct Process *p = lookup_process('m');
    next_process = p;
    asm volatile("ecall");
}
