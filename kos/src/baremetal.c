#include <stdint.h>
#include <stddef.h>

#include "baremetal.h"
#include "freedom_e.h"
#include "timer.h"
#include "process.h"
#include "uart.h"
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
            uart_putc(syscall_no + (int)'0');
        }
    }
}

// Syscalls for newlib

char *_sbrk(int incr)
{
    extern char memtop; /* Defined by baremetal.s */
    extern char _end;   /* Defined by the linker */

    static char *heap_end;
    char *prev_heap_end;
    if (heap_end == 0)
    {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;

    register char *sp asm("sp");

    char *max_heap_end;
    if (sp < &_end)
    {
        // calling from lightweight heapless process
        // so we can use the entire memory
        max_heap_end = &memtop;
    }
    else
    {
        // calling from system thread e.g. the scheduler or something
        // this assumption is gonna break if we ever dynamically allocation stacks
        max_heap_end = sp;
    }

    if (heap_end + incr > max_heap_end)
    {
        _write(1, "Heap out of space", 17);
        // abort();
    }

    heap_end += incr;
    return (char *)prev_heap_end;
}

#include <sys/stat.h>
int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}
int _lseek(int file, int offset, int whence)
{
    return 0;
}
int _close(int fd)
{
    return -1;
}
int _isatty(int file)
{
    return 1;
}