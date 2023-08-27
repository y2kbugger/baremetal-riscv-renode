#include <stdint.h>
#include <stdbool.h>
#define EMPTY_BUFFER -2

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

static int _buffer = EMPTY_BUFFER;
// Blocking fetch of single char
char getc()
{
    if (_buffer != EMPTY_BUFFER)
    {
        char val = _buffer;
        _buffer = EMPTY_BUFFER;
        return val;
    }
    while (uart->RxEmpty)
        ;
    return uart->RxTx;
}

// Nonblocking peek of next character
// If no character ready (buffered or raw), return -1
// If a character is ready return that character
// If no-one consumes a character inbetween calls, the char can be peeked again
int peekc()
{
    if (_buffer != EMPTY_BUFFER)
        return _buffer;
    else if (uart->RxEmpty)
        return -1;
    else
    {
        _buffer = uart->RxTx;
        return _buffer;
    }
}

void print_hex(uint32_t value)
{
    // Define hex characters
    const char hex_chars[] = "0123456789ABCDEF";

    // Print "0x" prefix
    putc('0');
    putc('x');

    int shift;
    bool leading_zero = true;

    // Process each 4-bit chunk (nibble)
    for (shift = 28; shift >= 0; shift -= 4)
    {
        char hex_char = hex_chars[(value >> shift) & 0xF];

        // Skip leading zeros
        if (hex_char == '0' && leading_zero && shift != 0)
        {
            continue;
        }

        if (hex_char != '0')
        {
            leading_zero = false;
        }

        putc(hex_char);
    }
}