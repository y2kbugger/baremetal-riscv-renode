image: baremetal.s baremetal.c
	riscv32-unknown-elf-gcc baremetal.s baremetal.c -ggdb -O0 -o image -ffreestanding -nostdlib

launch: image
	renode -P 45454 y2kvexriscv.resc

monitor:
	telnet localhost 45454

uart:
	telnet localhost 1234

debug:
	riscv32-unknown-elf-gdb -x gdbrc

clean:
	rm image
