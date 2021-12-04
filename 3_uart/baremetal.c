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

void init_uart();
void putc(char c);
void puts(char *str);
void fancy_char(char c);
void interrupt_handler() __attribute__((interrupt("machine")));

void init_uart()
{
    uart->EventEnable = RxEvent;
}

void interrupt_handler()
{
    fancy_char((char)uart->RxTx);
}

void putc(char c)
{
    uart->RxTx = c;
}

void puts(char *str)
{
    while (*str != '\0')
        putc(*str++);
}

void fancy_char(char c)
{
    char s[] = "\n###\n\r#X#\n\r###\n\r\n\r";
    s[7] = c;
    puts(s);
}
