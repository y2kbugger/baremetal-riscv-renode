#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

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

void init_uart()
{
    // uart->EventEnable = RxEvent;
}

bool uart_has_data()
{
    return !uart->RxEmpty;
}

int _write(int fd, char *buf, int count)
{
    int written = 0;

    for (; count != 0; --count)
    {
        while (uart->TxFull)
            ; // Wait until UART is not full
        uart->RxTx = *buf++;
        ++written;
    }
    return written;
}

int _read(int fd, char *buf, int count)
{
    int read = 0;

    while (uart->RxEmpty)
        ;

    for (; count > 0; --count)
    {
        *buf++ = uart->RxTx;
        read++;
        if (uart->RxEmpty)
            break;
    }

    return read;
}