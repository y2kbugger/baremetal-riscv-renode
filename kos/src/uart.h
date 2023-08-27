void init_uart();

char getc();
int peekc();

void putc(char c);
void puts(char *s);

void print_hex(uint32_t value);