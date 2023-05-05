# Development
https://blog.y2kbugger.com/baremetal-riscv-renode-1.html

After building toolschains, open VSCode to a subfolder project

## Toolchains
Toolchain submodules will not auto-update. You must manually checkout an updated version and rebuild the toolchain.

    make clean-deep
    make toolchain

## Running
Change into one of the example directory and activate the toolchain.

    cd 1_blinky
    source ../activate-toolchains.sh

Then in separate terminals start the tty watcher

    make uart-poll

and start the simulation

    make start

## Debugging
Then in 3 separate terminals start the tty watcher

    make uart-poll

and start the simulation

    make start

and then start the debugger

    make debug

## Help
For all information on all makefile targets run

    make help
