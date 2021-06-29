#include <stdint.h>
#include <unistd.h>

typedef struct
{
    uint32_t RxTx;
    uint32_t TxFull;
    uint32_t RxEmpty;
    uint32_t EventStatus;
    uint32_t EventPending;
    uint32_t EventEnable;
} UART;
const uint32_t TxEvent = 0b01;
const uint32_t RxEvent = 0b10;
volatile UART *const uart = (UART *)0x60001800;

#define PROC_STACK_SIZE 200

struct process
{
    size_t *sp;
    size_t stack[PROC_STACK_SIZE];
    char name;
};

void init_uart();
void init_processes();
void putc(char c);
void fancy_char(char c);
void swap_processes();

void aaa();
void bbb();

struct process a = {.name = 'a'};
struct process b = {.name = 'b'};
volatile struct process *current_process = NULL;

void init_uart()
{
    uart->EventEnable = RxEvent;
}

void init_processes()
{
    a.sp = &(a.stack[PROC_STACK_SIZE - 1]);
    b.sp = &(b.stack[PROC_STACK_SIZE - 1]);
    *(a.sp--) = (size_t)&aaa;
    *(b.sp--) = (size_t)&bbb;

    // another reg, a5
    *(a.sp--) = 0;
    *(b.sp--) = 0;
    // another reg, fp
    *(a.sp--) = 0;
    *(b.sp--) = 0;
}

void swap_processes()
{
    // consume buffer
    while (!uart->RxEmpty)
        uart->RxTx;
    putc('\n');

    if ('a' == current_process->name)
        current_process = &b;
    else
        current_process = &a;
}

void putc(char c)
{
    uart->RxTx = c;
}

void aaa()
{
    while (1)
        for (char c = '0'; c <= '9'; c++)
            putc(c);
}

void bbb()
{
    while (1)
        for (char c = 'a'; c <= 'z'; c++)
            putc(c);
}
