void putc(char c)
{
    __asm(".equ RxTx, 0x0");
    __asm("sb a0, RxTx(a2)");
}

void print(char *c)
{
    while (*c != '\0') {
        putc(*c++);
    }
}

void fancy_char(char c)
{
    /* char s[] = "######"; */
    /* print(s); */
    print("###\n#\0");
    putc(c);
    print("#\n###\n\n\0");
}
