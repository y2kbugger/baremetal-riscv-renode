GNUTCPREFIX = $(CURDIR)/riscv-gnu-toolchain-output
GNUTC = riscv-gnu-toolchain-output/bin/riscv32-unknown-elf-gcc
RENODETC = renode/output/bin/Release/Renode.exe

toolchains: $(GNUTC) $(RENODETC)

gcc: $(GNUTC)
renode: $(RENODETC)

$(GNUTC): riscv-gnu-toolchain/.git
	ld -lncurses 2> /dev/null || error 'ncurses headers to build gdb with the text user interface enabled.'
	cd riscv-gnu-toolchain && ./configure --prefix=$(GNUTCPREFIX) --disable-linux --with-arch=rv32i --with-riscv-attribute='yes' --enable-languages=c --enable-tui=yes
	cd riscv-gnu-toolchain && $(MAKE) -j4

$(RENODETC): renode/.git
	cd renode && ./build.sh

renode/.git:
	git submodule update --init --recursive renode

riscv-gnu-toolchain/.git:
	git submodule update --init --recursive riscv-gnu-toolchain

clean: clean-gcc clean-renode

clean-deep: clean-gcc-deep clean-renode-deep

clean-renode:
	cd renode && ./build.sh -c

clean-renode-deep:
	rm -rf renode

clean-gcc:
	cd riscv-gnu-toolchain && $(MAKE) clean
	rm -rf riscv-gnu-toolchain-output

clean-gcc-deep:
	rm -rf riscv-gnu-toolchain-output
	rm -rf riscv-gnu-toolchain
