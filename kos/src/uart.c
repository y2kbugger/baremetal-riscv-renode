#include <stdint.h>

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

void putc(char c)
{
    uart->RxTx = c;
}

void puts(char *s)
{
    while (*s != '\0')
        putc(*s++);
}

static char _buffer = '\0';
char getc()
{
    if (_buffer != '\0')
    {
        char val = _buffer;
        _buffer = '\0';
        return val;
    }
    while (uart->RxEmpty)
        ;
    return uart->RxTx;
}

// Nonblocking peek of next character
// If no character ready (buffered or raw), return NULL
// If character has already been peeked
//   AND there is a new char
//   disgard buffered char and peek again.
char peekc()
{
    if (uart->RxEmpty)
        return _buffer;
    else
    {
        _buffer = uart->RxTx;
        return _buffer;
    }
}