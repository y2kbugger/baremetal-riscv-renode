ifndef BAREMETAL_RISCV_RENODE
$(error Toolchain not activated. Be sure to `source ../activate-toolchains.sh`)
endif

image: *.s **/*.c
	riscv32-unknown-elf-gcc $^ -Wall -ggdb -O0 -o image -ffreestanding -nostdlib

launch: image
	renode vexriscv.resc --console

uart:
	netcat localhost 1234

debug:
	riscv32-unknown-elf-gdb -x gdbrc

clean:
	rm image
