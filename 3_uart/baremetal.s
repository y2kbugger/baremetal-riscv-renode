.equ UART_BASE, 0x60001800
.equ RxTx, 0x0
.equ TxFull, 0x04
.equ RxEmpty, 0x08
.equ EventStatus, 0x0c
.equ EventPending, 0x10
.equ EventEnable, 0x14

.section .text
.global _start      # Provide program starting address to linker

_start:

        # setup machine trap vector
1:      auipc   t0, %pcrel_hi(mtvec)        # load mtvec(hi)
        addi    t0, t0, %pcrel_lo(1b)       # load mtvec(lo)

        # The assembler pseudoinstruction to write a CSR, CSRW csr, rs1, is encoded as CSRRW x0, csr, rs1
        #csrrw   zero, mtvec, t0
        csrw   mtvec, t0

        # setup a stack pointer
        la sp, _stack

        # set mstatus.MIE=1 (enable M mode interrupts in general)
        li      t0, 0b0000000000001000
        csrrs   zero, mstatus, t0

        # set mie.MTIE=1 (enable M mode timer interrupts)
        li      t0, 0b0000000010000000
        csrrs   zero, mie, t0

        # set mie.MEIE=1 (enable M mode external interrupts)
        li      t0, 0b0000100000000000
        csrrs   zero, mie, t0

        call init_uart

sleep:
        wfi # wait for interrupt
        jal sleep

.align 4
# interrupt
mtvec:
        # Acknowledge received char
        li a2, UART_BASE
        lb a0, RxTx(a2)
        #addi a1, x0, 0b11
        #sb a1, EventPending(a2)

        # Put out some characters
        csrr t0, mcause
        call fancy_char

        mret

.common _stack,20000,0
