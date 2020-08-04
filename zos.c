void putc(char c)
{
    __asm(".equ RxTx, 0x0");
    __asm("sb a0, RxTx(a2)");
}

void put_fancy_asevens()
{
    putc('!');

    __asm(".equ RxTx, 0x0");
    __asm("addi a1, x5, '#'");
    __asm("sb a1, RxTx(a2)");
    __asm("sb a1, RxTx(a2)");

    __asm("addi a1, a7, 0");
    __asm("sb a1, RxTx(a2)");

    __asm("addi a1, x5, '#'");
    __asm("sb a1, RxTx(a2)");
    __asm("sb a1, RxTx(a2)");

    __asm("addi a1, x5, '\n'");
    __asm("sb a1, RxTx(a2)");
}
