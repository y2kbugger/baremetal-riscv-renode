next:
I want to stop a process and resume it.
    EOF can be sent via CTRL-D ('\004')
I want processes to be able make kernel ecalls and return to just after the call
I want other programs to be able to use the IO uninterupted while shell and others run int the background
    could have notion of fg and bg
    We could "peek" at next char and then ignore if it should belong to other process.
i want to know if a Process has blown stack
i want programs to be able to request sleep

Persistance. e.g. storage peripherial and filesystem
design Simple FPGA-able matrix-multiply accelerator
    high level or verilog?
verilate the matmul, attach to renode
driver for matmul
Run everything on a real FPGA

Usage:

You can launch process via a single char.
Multiple process can be queued simply by putting multiple process ids

    hlhlhl
