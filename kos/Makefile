ifndef BAREMETAL_RISCV_RENODE
$(error Toolchain not activated. Be sure to `source ../activate-toolchains.sh`)
endif

image: baremetal.s baremetal.c uart.c
	riscv32-unknown-elf-gcc baremetal.s baremetal.c uart.c -Wall -ggdb -O0 -o image -ffreestanding -nostdlib

launch: image
	renode vexriscv.resc --console

uart:
	telnet localhost 1234

debug:
	riscv32-unknown-elf-gdb -x gdbrc

clean:
	rm image
