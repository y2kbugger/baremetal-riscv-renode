.equ UART_BASE, 0x60001800
.equ RxTx, 0x0
.equ TxFull, 0x04
.equ RxEmpty, 0x08
.equ EventStatus, 0x0c
.equ EventPending, 0x10
.equ EventEnable, 0x14
# UART masks
.equ TxEvent, 0b01
.equ RxEvent, 0b10

.section .text
.global _start      # Provide program starting address to linker

_start:

# setup machine trap vector
1:      auipc   t0, %pcrel_hi(mtvec)        # load mtvec(hi)
        addi    t0, t0, %pcrel_lo(1b)       # load mtvec(lo)
        #csrrw   zero, mtvec, t0
# The assembler pseudoinstruction to write a CSR, CSRW csr, rs1, is encoded as CSRRW x0, csr, rs1
        csrw   mtvec, t0

# setup a stack pointer
        la sp, _stack

# set mstatus.MIE=1 (enable M mode interrupts in general)
        li      t0, 0b00001000
        csrrs   zero, mstatus, t0

# set mie.MTIE=1 (enable M mode timer interrupts)
        li      t0, 0b0000000010000000
        csrrs   zero, mie, t0

# set mie.MEIE=1 (enable M mode external interrupts)
        li      t0, 0b0000100000000000
        csrrs   zero, mie, t0

# set EnableEvents.rxevents = 1
        li a2, UART_BASE
        addi a1, x0, RxEvent
        sb a1, EventEnable(a2)

# just to show that we got here
        addi a3, x0, 0xBA

sleep:
        wfi # wait for interrupt
        j sleep

.align 4
# break on interrupt
mtvec:
# Acknowledge received char
        li a2, UART_BASE
        lb a7, RxTx(a2)
        #addi a1, x0, 0b11
        #sb a1, EventPending(a2)
# Put out some characters
        csrr t0, mcause
        li a2, UART_BASE

        call put_fancy_asevens

        addi a1, a7, 0
        sb a1, RxTx(a2)
        sb a1, RxTx(a2)
        sb a1, RxTx(a2)
        addi a1, x0, '\n'
        sb a1, RxTx(a2)

        addi a1, a7, 0
        sb a1, RxTx(a2)
        sb a1, RxTx(a2)
        sb a1, RxTx(a2)
        sb a1, RxTx(a2)
        addi a1, x0, '\n'
        sb a1, RxTx(a2)

        addi a1, a7, 0
        sb a1, RxTx(a2)
        sb a1, RxTx(a2)
        sb a1, RxTx(a2)
        addi a1, x0, '\n'
        sb a1, RxTx(a2)

        mret

putbyte: # char in a1
        li a2, UART_BASE
        sb a1, RxTx(a2)
        ret

.common _stack,200,0
