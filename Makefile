CC = riscv-gnu-toolchain-output/bin/riscv32-unknown-elf-gcc

target:
	$(CC) irq.s -ggdb -O0 -o h -ffreestanding -nostdlib
