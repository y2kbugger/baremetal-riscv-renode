ifndef BAREMETAL_RISCV_RENODE
$(error Toolchain not activated. Be sure to `source ../activate-toolchains.sh`)
endif

help:	## Show this help.
	@sed -ne 's/^\([^[:space:]]*\):.*##/\1:\t/p' $(MAKEFILE_LIST) | column -t -s $$'\t'

image:	baremetal.s baremetal.c ## Build the image
	riscv32-unknown-elf-gcc $^ -march=rv32i_zicsr -Wall -ggdb -O0 -o image -ffreestanding -nostdlib

launch: image ## Image Launch the image in renode
	renode --net vexriscv.resc --console

start: image ## Launch the image in renode and start the simulation
	renode --net -e "include @vexriscv.resc" -e "start" --console

uart:	## Attach to the simulation uart
	stty -icanon -isig -echo && netcat localhost 1234 && stty sane

uart-poll:	## Continuous watch for and attach to the simulation uart
	@printf ...\\n; while true; do stty -icanon -isig -echo; netcat localhost 1234 2>/dev/null && printf \\n...\\n; stty sane; sleep 1; done;

debug:	## Start and attach gdb to the simulation
	riscv32-unknown-elf-gdb -x gdbrc

clean: ## Remove build artifacts
	rm image