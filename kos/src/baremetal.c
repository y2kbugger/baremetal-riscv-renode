#include <stdint.h>
#include <stddef.h>

#include "baremetal.h"
#include "freedom_e.h"
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
}

void schedule_processes()
{
    if (next_process == NULL)
        next_process = next_process_of_status(current_process, Ready, true);

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

#define MCAUSE_INT_MASK 0x80000000
#define MCAUSE_CODE_MASK 0x7FFFFFFF
void handle_interrupt()
{
    unsigned long mcause_value = read_csr(mcause);
    unsigned long mcause_code = mcause_value & MCAUSE_CODE_MASK;

    if (mcause_value & MCAUSE_INT_MASK)
    {
        // interrupt
        if (mcause_code == 11)
        {
            // machine external
        }
        else if (mcause_code == 7)
        {
            // machine timer
            schedule_processes();
            clear_timer();
        }
    }
    else
    {
        // exception specific
        if (mcause_code == 11)
        {
            // ecall
            if (current_process == NULL)
                return;

            size_t *mepc = current_process->sp + 29;
            *mepc += 4;

            register unsigned long syscall_no asm("a7");
            putc(syscall_no + (int)'0');
        }
    }
}
