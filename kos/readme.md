I want:
- processes to be able make kernel ecalls and return to just after the call
- all Process mutating functions to happen via kernel call so that race conditions are rendered impossible. e.g. stop all running processes is current called straight from the shell.
- shell to handle line editing so multi-character commands will be possible
- to know if a Process has blown stack
- programs to be able to request sleep
- to  be able to recycle process objects
- count forever to count higher than 9
- I want to be able to persist data between launches
    - so that I can make a file editor
    - so that I can make a filesystem
    - so that I can write another driver and learn mass storage
- to design Simple FPGA-able matrix-multiply accelerator
    - verilate the matmul, attach to renode
    - write driver for matmul
- Run everything on a real FPGA

Bugs:
- crash because of requesting an unregistered program name
