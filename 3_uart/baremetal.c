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
    uart->EventEnable = RxEvent;
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
    char s[] = "###\n\r#X#\n\r###\n\r\n\r";
    s[6] = c;
    puts(s);
}
