void putc(char c)
{
    __asm(".equ RxTx, 0x0");
    __asm("sb a0, RxTx(a2)");
}

void print(char *c)
{
    __asm(".equ UART_BASE, 0x60001800");
    __asm("li a2, UART_BASE");
    while (*c != '\0') {
        putc(*c++);
    }
}

void fancy_char(char c)
{
    char s[] = "###\n\r#X#\n\r###\n\r\n\n";
    s[6] = c;
    print(s);
}
