# Active
- to handle escape sequences in the shell

# Backlog
I want:
- slow down count forever and laugh forever
- to not have to manually put end this function in program definition.
- all Process mutating functions to happen via kernel call so that race conditions are rendered impossible. e.g. stop all running processes is current called straight from the shell.
- programs to be able to request sleep
- to  be able to recycle process objects
- shell to handle line editing so multi-character commands will be possible
- to know if a Process has blown stack
- count forever to count higher than 9
- dynamic memory allocation so that stack size and process count are not fixed at compile time.
  - this automatically handles the recycling of process objects
- memory space isolation for processes so that one process cannot crash the entire system.
- to be able to load in programs at runtime e.g. binary over serial
- I want to be able to persist data between launches
    - so that I can make a file editor
    - so that I can make a filesystem
    - so that I can write another driver and learn mass storage
- to design Simple FPGA-able matrix-multiply accelerator
    - verilate the matmul, attach to renode
    - write driver for matmul
- Run everything on a real FPGA

# Bugs
-
