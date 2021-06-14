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

void init_uart();
void putc(char c);
void fancy_char(char c);
void interrupt_handler() __attribute__((interrupt("machine")));

void aaa();
void bbb();

void init_uart()
{
    uart->EventEnable = RxEvent;
}

char process = 'a';
size_t context_sp_a = (size_t)&aaa;
size_t context_sp_b = (size_t)&bbb;

void interrupt_handler()
{
    while (!uart->RxEmpty)
        uart->RxTx = uart->RxTx;

    if ('a' == process)
    {
        process = 'b';
    }
    else
    {
        process = 'a';
    }
}

void putc(char c)
{
    uart->RxTx = c;
}

void aaa()
{
    while (1)
        putc('a');
}

void bbb()
{
    while (1)
        putc('b');
}
