ifndef BAREMETAL_RISCV_RENODE
$(error Toolchain not activated. Be sure to `source ../activate-toolchains.sh`)
endif

image: baremetal.s baremetal.c
	riscv32-unknown-elf-gcc baremetal.s baremetal.c -Wall -ggdb -O0 -o image -ffreestanding -nostdlib

launch: image
	renode vexriscv.resc --console

start: image
	renode -e "include @vexriscv.resc" -e "start" --console

uart:
	stty -icanon && netcat localhost 1235 && stty sane

uart-poll:
	@printf ...\\n; while true; do stty -icanon -isig; netcat localhost 1235 2>/dev/null && printf \\n...\\n; stty sane; sleep 1; done;

debug:
	riscv32-unknown-elf-gdb -x gdbrc

clean:
	rm image
