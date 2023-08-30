include ../Makefile.common

verilation:	## Build the verilated model
	mkdir -p ../verilation/build
	cd ../verilation/build && cmake -DCMAKE_BUILD_TYPE=Release -DUSER_RENODE_DIR="$$BAREMETAL_RISCV_RENODE" -DLIBOPENLIBM=$$BAREMETAL_RISCV_RENODE/renode-verilator-integration/lib/libopenlibm-Linux-x86_64.a ".."
	$(MAKE) -C ../verilation/build libVtop

launch: verilation
	$(MAKE) -f ../Makefile.common $@

start: verilation
	$(MAKE) -f ../Makefile.common $@