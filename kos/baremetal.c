#include <stdint.h>
#include <unistd.h>

#include "uart.h"

#define PROC_STACK_SIZE 200

struct process
{
    size_t *sp;
    size_t stack[PROC_STACK_SIZE];
    char name;
};

void init_processes();
void swap_processes();

void aaa();
void bbb();

struct process a = {.name = 'a'};
struct process b = {.name = 'b'};
volatile struct process *current_process = NULL;

void init_monitor()
{
    a.sp = &(a.stack[PROC_STACK_SIZE - 1]);
    b.sp = &(b.stack[PROC_STACK_SIZE - 1]);
    *(a.sp--) = (size_t)&aaa;
    *(b.sp--) = (size_t)&bbb;

    for (size_t i = 28; i > 0; i--)
    {
        *(a.sp--) = 0xdeedbeef;
        *(b.sp--) = 0xdeedbeef;
    }
    getc(); // Hit enter after boot to get a prompt
    puts("I Love you, Sara.");
}

void swap_processes()
{
    putc('\n');

    if ('a' == current_process->name)
        current_process = &b;
    else
        current_process = &a;
}

void aaa()
{
    putc('$');
    while (1)
        for (char c = '0'; c <= '9'; c++)
            putc(c);
}

void bbb()
{
    putc('#');
    while (1)
        for (char c = 'a'; c <= 'z'; c++)
            putc(c);
}
