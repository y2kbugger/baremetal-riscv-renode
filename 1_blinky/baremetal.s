.equ LED, 0x60000800
.equ DELAY_COUNT, 9000000
.equ LED_STATE_INITIAL, 0b00
.equ LED_STATE_TOGGLE_MASK, 0b01

.section .text
.global _start
_start:
        li a5, LED
        li a4, LED_STATE_INITIAL
        li a6, LED_STATE_TOGGLE_MASK
        sw a4, 0x0(a5)
loop:
        li a0, DELAY_COUNT      # reset counter
delay_loop:
        addi a0, a0, -1         # count down
        bnez a0, delay_loop
toggle_led:
        lw a4, 0x0(a5)          # read in old led state
        xor a4, a4, a6          # toggle led state word
        sw a4, 0x0(a5)          # write new state
        jump loop, t0
