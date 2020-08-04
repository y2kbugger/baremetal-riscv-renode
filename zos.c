void putc(char c)
{
    __asm(".equ RxTx, 0x0");
    __asm("sb a0, RxTx(a2)");
}

void fancy_char(char c)
{
    putc('#');
    putc('#');
    putc('#');
    putc('\n');
    putc('#');
    putc(c);
    putc('#');
    putc('\n');
    putc('#');
    putc('#');
    putc('#');
    putc('\n');
    putc('\n');
}
