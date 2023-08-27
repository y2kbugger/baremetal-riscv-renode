# Active
- shell to handle line editing so multi-character commands will be possible
    - currently the yell function is a hardcoded example, but we still fall back to single letter programs. Need to integrate the multi-character names into the process struct and then remove the yell example.
- to handle escape sequences in the shell
    - currently escape sequences are bugged and sometimes print garbage when hitting up arrow.
- to handle backspace in the shell

# Backlog
I want:
- programs should be able to self-document e.g. don't hardcode usage
- programs to be able to request sleep
- slow down count forever and laugh forever
- count forever to count higher than 9
- to not have to manually put end this function in program definition.
- to be able to recycle process objects
- dynamic memory allocation so that stack size and process count are not fixed at compile time.
  - this automatically handles the recycling of process objects
- shells should forward input to programs
    - right now, all programs can grab user input based the race of who gets to read the UART during multi-tasking
- to design Simple FPGA-able matrix-multiply accelerator
    - verilate the matmul, attach to renode
    - write driver for matmul
- Run everything on a real FPGA
- all Process mutating functions to happen via kernel call so that race conditions are rendered impossible.
    - e.g. stop all running processes is current called straight from the shell.
- memory space isolation for processes so that one process cannot crash the entire system.
- to be able to load in programs at runtime e.g. binary over serial
- I want to be able to persist data between launches
    - so that I can make a file editor
    - so that I can make a filesystem
    - so that I can write another driver and learn mass storage
- to know if a Process has blown stack
- explore this update to renode: "GDB autostart parameter now starts the simulation as soon as the debugger is connected" and "GDB interacts with Renode much faster"
- explore this update to renode: "handling of c.ebreak instruction in RISC-V, allowing for software breakpoints"
- does this cause problems? "VerilatorIntegrationLibrary is now part of Renode packages"
- explore update "support for NMI interrupts in RISC-V"
- explore riscv vector instructions

# Bugs
-
