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
2:
        addi a0, a0, 1
        addi a1, a0, 0
        jal ra, putbyte # call subroutine
        #jal ra, readstatus
        j 2b

putbyte: # char in a1
        li a2, UART_BASE
        sb a1, RxTx(a2)
        ret

readstatus:
        li a2, UART_BASE
        lb a0, EventPending(a2)
        ret


irq:
        addi a1, x0, 69
        jal ra, putbyte # call subroutine
        mret # return from interrupt in machine mode


.section .data
helloworld:      .ascii "Y2k"
