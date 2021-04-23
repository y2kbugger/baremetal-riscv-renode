ifndef BAREMETAL_RISCV_RENODE
$(error Toolchain not activated. Be sure to `source ../activate-toolchains.sh`)
endif

image: baremetal.s baremetal.c
	riscv32-unknown-elf-gcc baremetal.s baremetal.c -Wall -pedantic -ggdb -O0 -o image -ffreestanding -nostdlib

launch: image
	renode vexriscv.resc

uart:
	telnet localhost 1234

debug:
	riscv32-unknown-elf-gdb -x gdbrc

clean:
	rm image
