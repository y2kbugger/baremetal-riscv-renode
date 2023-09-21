.global memtop
.equ memtop, 0x00050000
.equ XLEN, 4 # 32 bit, 4*8

.section .text
.global _start      # Provide program starting address to linker

_start:

        # setup machine trap vector
1:      auipc   t0, %pcrel_hi(mtvec_interrupt_handler)  # load mtvec_interrupt_handler(hi)
        addi    t0, t0, %pcrel_lo(1b)                   # load mtvec_interrupt_handler(lo)
        csrw   mtvec, t0

        # set mstatus.MIE=1 (enable M mode interrupts in general)
        li      t0, 0b0000000000001000
        csrrs   zero, mstatus, t0

        # set mie.MTIE=1 (enable M mode timer interrupts)
        li      t0, 0b0000000010000000
        csrrs   zero, mie, t0

        # set mie.MEIE=1 (enable M mode external interrupts)
        li      t0, 0b0000100000000000
        csrrs   zero, mie, t0

        # setup a stack pointer
        la sp, memtop

        # no process is running by default
        # squat on tp to hold which process is running
        # linux kinda does this sooo..
        li tp, 0

        # setup gp
        .option push
        .option norelax
        la gp, __global_pointer$
        .option pop

        call init_kernel

forever:
        j forever

mtvec_interrupt_handler:
        # skip saving if not process started yet
        beq     tp, zero, no_current_process

store_process:
        addi    sp, sp, -32*XLEN   # allocate space for context

        # store all registers
        sw      x1, 1*XLEN(sp)
        #       x2(sp)
        #       x3(gp)
        #       x4(tp)
        sw      x5, 2*XLEN(sp)
        sw      x6, 3*XLEN(sp)
        sw      x7, 4*XLEN(sp)
        sw      x8, 5*XLEN(sp)
        sw      x9, 6*XLEN(sp)
        sw      x10, 7*XLEN(sp)
        sw      x11, 8*XLEN(sp)
        sw      x12, 9*XLEN(sp)
        sw      x13, 10*XLEN(sp)
        sw      x14, 11*XLEN(sp)
        sw      x15, 12*XLEN(sp)
        sw      x16, 13*XLEN(sp)
        sw      x17, 14*XLEN(sp)
        sw      x18, 15*XLEN(sp)
        sw      x19, 16*XLEN(sp)
        sw      x20, 17*XLEN(sp)
        sw      x21, 18*XLEN(sp)
        sw      x22, 19*XLEN(sp)
        sw      x23, 20*XLEN(sp)
        sw      x24, 21*XLEN(sp)
        sw      x25, 22*XLEN(sp)
        sw      x26, 23*XLEN(sp)
        sw      x27, 24*XLEN(sp)
        sw      x28, 25*XLEN(sp)
        sw      x29, 26*XLEN(sp)
        sw      x30, 27*XLEN(sp)
        sw      x31, 28*XLEN(sp)

        # store pc from the process onto the stack
        csrr    t0, mepc
        sw      t0, 31*XLEN(sp)

        # store sp from the process
        # current_process->sp = sp
        sw      sp, 0(tp)

no_current_process:
        la      sp, memtop # Switch to ISR stack before calling function
        call    handle_interrupt

        # squat on tp to hold current process and not get clobbered
        lui     tp, %hi(current_process)
        lw      tp, %lo(current_process)(tp)

restore_process:
        # restore sp from the process
        # sp = current_process->sp
        lw      sp, 0(tp)

        # restore pc into mepc
        lw      t0, 31*XLEN(sp)
	csrw    mepc, t0

        # restore all registers
        lw      x1, 1*XLEN(sp)
        #       x2(sp)
        #       x3(gp)
        #       x4(tp)
        lw      x5, 2*XLEN(sp)
        lw      x6, 3*XLEN(sp)
        lw      x7, 4*XLEN(sp)
        lw      x8, 5*XLEN(sp)
        lw      x9, 6*XLEN(sp)
        lw      x10, 7*XLEN(sp)
        lw      x11, 8*XLEN(sp)
        lw      x12, 9*XLEN(sp)
        lw      x13, 10*XLEN(sp)
        lw      x14, 11*XLEN(sp)
        lw      x15, 12*XLEN(sp)
        lw      x16, 13*XLEN(sp)
        lw      x17, 14*XLEN(sp)
        lw      x18, 15*XLEN(sp)
        lw      x19, 16*XLEN(sp)
        lw      x20, 17*XLEN(sp)
        lw      x21, 18*XLEN(sp)
        lw      x22, 19*XLEN(sp)
        lw      x23, 20*XLEN(sp)
        lw      x24, 21*XLEN(sp)
        lw      x25, 22*XLEN(sp)
        lw      x26, 23*XLEN(sp)
        lw      x27, 24*XLEN(sp)
        lw      x28, 25*XLEN(sp)
        lw      x29, 26*XLEN(sp)
        lw      x30, 27*XLEN(sp)
        lw      x31, 28*XLEN(sp)

        addi    sp, sp, 32*XLEN   # deallocate space for context

        mret
