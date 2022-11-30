ifndef BAREMETAL_RISCV_RENODE
$(error Toolchain not activated. Be sure to `source ../activate-toolchains.sh`)
endif

image: baremetal.s
	riscv32-unknown-elf-gcc baremetal.s -march=rv32imac -ggdb -O0 -o image -ffreestanding -nostdlib

launch: image
	renode vexriscv.resc

debug:
	riscv32-unknown-elf-gdb -x gdbrc

clean:
	rm image
