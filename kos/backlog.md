# Active
- implement SIGINT and SIGKILL/SIGSTOP/SIGTERM using actual signals, this will fix the ctrl-c bug
  - this would help make the shell simpler and more robust
  - it removes the need to peek for SIGINT in the shell using buffered input.
  - right now we work around it with bool uart_has_data(), but true asyncronous signals would be interesting to learn.

# On Deck
- shell to handle line editing so multi-character commands will be possible
    - currently the yell function is a hardcoded example, but we still fall back to single letter programs. Need to integrate the multi-character names into the process struct
- to handle escape sequences in the shell
    - currently escape sequences are bugged and sometimes print garbage when hitting up arrow.
- to handle backspace in the shell
- programs should be able to self-document e.g. don't hardcode usage
- tab completion in shell

# Backlog
I want:
- redefine stack using uint8_t (also same for heap e.g. _sbrk)
- to be able to recycle process objects
- programs to be able to request sleep (e.g. sleep 1 second unless interrupted by signal)
- programs to be able to request pause (e.g. sleep indefinitly unless interrupted by signal)
- slow down count forever and laugh forever
- shell should be able to list all shell options as well as current value
- all Process mutating functions to happen via kernel call so that race conditions are rendered impossible.
    - e.g. stop all running processes is current called straight from the shell.
- memory space isolation for processes so that one process cannot crash the entire system.
- dynamic memory allocation so that stack size and process count are not fixed at compile time.
  - this automatically handles the recycling of process objects
- to not have to manually put end this function in program definition.
- Run everything on a real FPGA
- to be able to load in programs at runtime e.g. binary over serial
- I want to be able to persist data between launches
    - so that I can make a file editor
    - so that I can make a filesystem
    - so that I can write another driver and learn mass storage
- explore this update to renode: "handling of c.ebreak instruction in RISC-V, allowing for software breakpoints"
- explore update "support for NMI interrupts in RISC-V"
- explore riscv vector instructions
- compile newlib with gdb symbols so that I can debug through the newlib code

# Bugs
- ctrl-c fails if an unget c is in the buffer before the ctrl-c

# Memory map

0x00000
  ...   unused
0x10000            RAM BOTTOM
0x10094 _start
  ...   system image
0x18000 _end
  ...   heap - grows down (if implemented)
  ...   stack - grows up
0x50000 memtopi    RAM TOP