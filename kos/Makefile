include ../Makefile.common

verilator::
	mkdir -p ../verilation/build
	cd ../verilation/build && cmake -DCMAKE_BUILD_TYPE=Release -DUSER_RENODE_DIR="$$BAREMETAL_RISCV_RENODE" -DLIBOPENLIBM=$$BAREMETAL_RISCV_RENODE/renode-verilator-integration/lib/libopenlibm-Linux-x86_64.a ".."
	$(MAKE) -C ../verilation/build libVtop

clean-verilator::
	rm -rf ../verilation/build

tests:	test/test.c ## Build the tests
	riscv32-unknown-elf-gcc $^ -march=rv32i_zicsr -Wall -ggdb -O0 -o tests -lgcc

test: tests ## Run the tests
	qemu-riscv32-static tests