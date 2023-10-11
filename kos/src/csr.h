// Borrowed from Si-five freedom-e SDK
// See https://github.com/sifive/freedom-e-sdk/blob/fa2a87344c1d48973bdcddcb0c501685f3723554/LICENSE
#define read_csr(reg) _read_csr(reg)
#define _read_csr(reg) (              \
    {                                 \
        unsigned long __tmp;          \
        asm volatile("csrr %0, " #reg \
                     : "=r"(__tmp));  \
        __tmp;                        \
    })

#define write_csr(reg) _write_csr(reg, bits)
#define _write_csr(reg, bits)            \
    {                                    \
        unsigned long __tmp = (bits);    \
        asm volatile("csrw " #reg ", %0" \
                     :                   \
                     : "rK"(__tmp));     \
    }

#define set_csr(reg, bitmask) _set_csr(reg, bitmask)
#define _set_csr(reg, bitmask)           \
    {                                    \
        asm volatile("csrs " #reg ", %0" \
                     :                   \
                     : "r"(bitmask));    \
    }

#define clear_csr(reg, bitmask) _clear_csr(reg, bitmask)
#define _clear_csr(reg, bitmask)         \
    {                                    \
        asm volatile("csrc " #reg ", %0" \
                     :                   \
                     : "r"(bitmask));    \
    }
