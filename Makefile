gccprefix = $(CURDIR)/riscv-gnu-toolchain-output
export PATH := $(gccprefix):$(PATH)
CC = riscv32-unknown-elf-gcc

zos: riscv-gnu-toolchain-output/bin/$(CC) zos.s zos.c
	$(CC) zos.s zos.c -ggdb -O0 -o zos -ffreestanding -nostdlib

debug: zos renode/renode
	./renode/renode -P 45454 y2kvexriscv.resc
	# xterm -e 'telnet localhost 45454' &
	# xterm -e 'riscv32-unknown-elf-gdb -x gdbrc' &

riscv-gnu-toolchain renode:
	git submodule update --init --recursive

riscv-gnu-toolchain-output/bin/$(CC): riscv-gnu-toolchain/.git
	cd riscv-gnu-toolchain && ./configure --prefix=$(gccprefix) --disable-linux --with-arch=rv32i --with-riscv-attribute='yes'  --enable-languages=c
	cd riscv-gnu-toolchain && make

renode/renode: renode/.git
	cd renode && ./build.sh

clean:
	cd riscv-gnu-toolchain && make clean
	cd renode && ./build.sh -c

clean-deep: clean
	rm -rf riscv-gnu-toolchain-output
	rm -rf riscv-gnu-toolchain
	rm -rf renode
