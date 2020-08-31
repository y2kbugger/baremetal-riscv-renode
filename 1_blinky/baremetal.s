.equ LED, 0x60000800

.section .text
.global _start

_start:
        li a0, 0x00
        li a0, 0x00
        li a3, 0x1200000
        li a5, LED
loop:
        addi a0, a0, 0x01
        bne a0, a3,  loop

toggle_led:
        lw a4, 0x0(a5)
        xori a4, a4, 0x1
        sw a4, 0x0(a5)
        jump _start, t0
