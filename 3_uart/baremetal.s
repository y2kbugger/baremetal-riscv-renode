.equ memtop, 0x00040000

.section .text
.global _start      # Provide program starting address to linker

_start:

        # setup machine trap vector
1:      auipc   t0, %pcrel_hi(mtvec_interrupt_handler)  # load mtvec_interrupt_handler(hi)
        addi    t0, t0, %pcrel_lo(1b)                   # load mtvec_interrupt_handler(lo)
        csrw   mtvec, t0

        # setup a stack pointer
        la sp, memtop

        # set mstatus.MIE=1 (enable M mode interrupts in general)
        li      t0, 0b0000000000001000
        csrrs   zero, mstatus, t0

        # set mie.MEIE=1 (enable M mode external interrupts)
        li      t0, 0b0000100000000000
        csrrs   zero, mie, t0

        call init_uart

wait_for_interrupt:
        wfi
        j wait_for_interrupt

.align 4
mtvec_interrupt_handler:
        j interrupt_handler
