.equ UART_BASE, 0x60001800
.equ RxTx, 0x0
.equ TxFull, 0x04
.equ RxEmpty, 0x08
.equ EventStatus, 0x0c
.equ EventPending, 0x10
.equ EventEnable, 0x14

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

        # setup gp
        .option push
        .option norelax
        la gp, __global_pointer$
        .option pop

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
        call init_processes

forever:
        j forever

mtvec_interrupt_handler:

        # a1 <- current_process->sp (sp is first field)
        lui     t1,%hi(current_process)
        lw      a1,%lo(current_process)(t1)

        #skip saving if not process started yet
        beq     a1, zero, no_current_process

        # store pc from the process onto the stack
        csrr    a2, mepc
        sw      a2, 0(sp)
        addi    sp, sp, -4
        # store another reg, a5
        sw      a5, 0(sp)
        addi    sp, sp, -4
        # store another reg, fp
        sw      fp, 0(sp)
        addi    sp, sp, -4
        # store sp from the process
        # current_process->sp = sp
        sw      a1, 0(sp)

no_current_process:
        call swap_processes

        # a1 <- current_process->sp (sp is first field)
        lui     t1,%hi(current_process)
        lw      a1,%lo(current_process)(t1)

        # restore sp from the process
        # sp = current_process->sp
        lw      sp, 0(a1)
        # restore another reg, fp
        addi    sp,sp,4
        lw      fp,0(sp)
        # restore another reg, a5
        addi    sp,sp,4
        lw      a5,0(sp)
        # restore pc from the process
        addi    sp,sp,4
        lw      a2,0(sp)
	csrw    mepc, a2

        mret

.common lol, 1000, 'U'
