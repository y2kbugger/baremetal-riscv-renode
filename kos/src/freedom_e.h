// Borrowed from Si-five freedom-e SDK
// See https://github.com/sifive/freedom-e-sdk/blob/fa2a87344c1d48973bdcddcb0c501685f3723554/LICENSE
#define read_csr(reg) _read_csr_value(reg)
#define _read_csr_value(reg) (        \
    {                                 \
        unsigned long __tmp;          \
        asm volatile("csrr %0, " #reg \
                     : "=r"(__tmp));  \
        __tmp;                        \
    })
