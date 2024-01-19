ifndef BAREMETAL_RISCV_RENODE
$(error Toolchain not activated. Be sure to `source ../activate-toolchains.sh`)
endif

help:	## Show this help.
	@sed -ne 's/^\([^[:space:]]*\):.*##/\1:\t/p' $(MAKEFILE_LIST) | column -t -s $$'\t'

image:	baremetal.s ## Build the image
	riscv32-unknown-elf-gcc $^ -march=rv32i_zicsr -Wall -ggdb -O0 -o image -ffreestanding -nostdlib

launch: image ## Image Launch the image in renode
	renode --net vexriscv.resc --console

start: image ## Launch the image in renode and start the simulation
	renode --net -e "include @vexriscv.resc" -e "start" --console

debug:	## Start and attach gdb to the simulation
	riscv32-unknown-elf-gdb -x gdbrc

clean: ## Remove build artifacts
	rm image
