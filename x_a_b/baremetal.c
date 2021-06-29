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

struct process
{
    size_t pc;
    int32_t stack[200];
    char name;
};

void init_uart();
void putc(char c);
void fancy_char(char c);
void swap_processes();

void aaa();
void bbb();

void init_uart()
{
    uart->EventEnable = RxEvent;
}

struct process a = {.pc = (size_t)&aaa, .name = 'a'};
struct process b = {.pc = (size_t)&bbb, .name = 'b'};
struct process *current_process = &a;

void swap_processes()
{
    // echo loopback
    while (!uart->RxEmpty)
        uart->RxTx = uart->RxTx;

    if ('a' == current_process->name)
    {
        current_process = &b;
    }
    else
    {
        current_process = &a;
    }
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
