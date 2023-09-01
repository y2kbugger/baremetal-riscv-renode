#include <stdint.h>
#include <stdbool.h>

#include "./mutex.h"

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

struct Mutex _buffer_mutex;
void init_uart()
{
    mutex_init(&_buffer_mutex);
    // uart->EventEnable = RxEvent;
}

void putc(char c)
{
    while (uart->TxFull)
        ; // Wait until UART is not full
    uart->RxTx = c;
}

void puts(char *s)
{
    while (*s != '\0')
        putc(*s++);
}

volatile int _buffer = EMPTY_BUFFER;
// Blocking fetch of single char
char getc()
{
    char retval;
    mutex_lock(&_buffer_mutex);
    if (_buffer != EMPTY_BUFFER)
    {
        char val = _buffer;
        _buffer = EMPTY_BUFFER;
        retval = val;
    }
    else
    {
        while (uart->RxEmpty)
            ;
        retval = uart->RxTx;
    }
    mutex_unlock(&_buffer_mutex);
    return retval;
}

// Nonblocking peek of next character
// If no character ready (buffered or raw), return -1
// If a character is ready return that character
// If no-one consumes a character inbetween calls, the char can be peeked again
int peekc()
{
    int retval;

    mutex_lock(&_buffer_mutex);

    if (_buffer != EMPTY_BUFFER)
    {
        retval = _buffer;
    }
    else if (uart->RxEmpty)
    {
        retval = -1;
    }
    else
    {
        _buffer = uart->RxTx;
        retval = _buffer;
    }

    mutex_unlock(&_buffer_mutex);

    return retval;
}

void print_hex(uint32_t value, int bit_width)
{
    // Define hex characters
    const char hex_chars[] = "0123456789ABCDEF";

    // Print "0x" prefix
    puts("0x");

    // Process each 4-bit chunk (nibble)
    for (int shift = bit_width - 4; shift >= 0; shift -= 4)
    {
        char hex_char = hex_chars[(value >> shift) & 0xF];
        putc(hex_char);
    }
}

uint32_t read_hex_double_word()
{
    puts("Enter a 32-bit hex number: 0x");
    uint32_t value = 0;
    int count = 0;
    while (count < 8)
    { // A 32-bit hex number is up to 8 characters long
        int ch = getc();

        // Convert hex char to integer
        if (ch >= '0' && ch <= '9')
        {
            value = (value << 4) | (ch - '0');
        }
        else if (ch >= 'a' && ch <= 'f')
        {
            value = (value << 4) | (ch - 'a' + 10);
        }
        else if (ch >= 'A' && ch <= 'F')
        {
            value = (value << 4) | (ch - 'A' + 10);
        }
        else
        {
            puts("Invalid character encountered.");
            return 0; // Or any other error handling mechanism
        }
        putc(ch);

        count++;
    }
    putc('\n');
    return value;
}