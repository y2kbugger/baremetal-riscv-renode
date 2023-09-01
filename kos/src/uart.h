#include <stdint.h>

void init_uart();

char getc();
int peekc();

void putc(char c);
void puts(char *s);