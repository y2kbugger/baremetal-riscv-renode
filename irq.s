.equ UART_BASE, 0x60001800
.equ RxTx, 0x0
.equ TxFull, 0x04
.equ RxEmpty, 0x08
.equ EventStatus, 0x0c
.equ EventPending, 0x10
.equ EventEnable, 0x14

.section .text
.global _start      # Provide program starting address to linker

# Loop forever counting on a0
_start: addi a0, x0, 1
# setup machine trap vector
1:      auipc   t0, %pcrel_hi(mtvec)        # load mtvec(hi)
        addi    t0, t0, %pcrel_lo(1b)       # load mtvec(lo)
        csrrw   zero, mtvec, t0

# set mstatus.MIE=1 (enable M mode interrupt)
        li      t0, 8
        csrrs   zero, mstatus, t0

sleep:
        wfi # wait for interrupt
        j sleep

# break on interrupt
mtvec:
        j print_and_sleep

print_and_sleep:
        la a0, pass_msg
        j sleep


.section .rodata

pass_msg:
        .string "PASS\n"
