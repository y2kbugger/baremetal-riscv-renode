ifndef BAREMETAL_RISCV_RENODE
$(error Toolchain not activated. Be sure to `source ../activate-toolchains.sh`)
endif

image: src/*.s src/*.c src/**/*.c
	riscv32-unknown-elf-gcc $^ -march=rv32i_zicsr -Wall -ggdb -O0 -o image -ffreestanding -nostdlib -lgcc

launch: image
	renode vexriscv.resc --console

start: image
	renode -e "include @vexriscv.resc" -e "start" --console

uart:
	stty -icanon && netcat localhost 1234 && stty sane

uart-poll:
	@printf ...\\n; while true; do stty -icanon -isig; netcat localhost 1234 2>/dev/null && printf \\n...\\n; stty sane; sleep 1; done;

debug:
	riscv32-unknown-elf-gdb -x gdbrc

clean:
	rm image
