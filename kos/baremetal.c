#include <stdint.h>
#include <unistd.h>

#include "uart.h"
#include "process.h"
#include "processes/processes.h"

volatile struct Process *current_process = NULL;

void init_monitor()
{
    init_all_processes();

    puts("Choose a program to start:\n");
    puts(" h: hello world\n");
    puts(" l: laugh\n");

    current_process = lookup_process(getc());
    asm volatile("ecall");
}

void schedule_processes()
{
}
