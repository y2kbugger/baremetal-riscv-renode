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
1:      auipc   t0, %pcrel_hi(mtvec_interrupt_handler)  # load mtvec_interrupt_handler(hi)
        addi    t0, t0, %pcrel_lo(1b)                   # load mtvec_interrupt_handler(lo)
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

forever:
        j forever

.extern current_process;
.extern bbb;
.align 4
mtvec_interrupt_handler:

        # get the old process
        # lui     t1,%hi(current_process)
        # lw      t1,%lo(current_process)(t1)

        # store sp from the process
        # store_x  sp, 0( t0 )

        # store pc from the process
        csrr a1, mepc
        sw a1, 0(t1)

        call swap_processes

        # get the new process
        lui     t1,%hi(current_process)
        lw      t1,%lo(current_process)(t1)

        # set sp from the process
        addi      sp, t1, 4

        # set pc from the process
        lw      t1,0(t1)
	csrw    mepc, t1

        mret

.common _stack, 20000, 0
