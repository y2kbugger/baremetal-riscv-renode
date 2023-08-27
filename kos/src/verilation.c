#include <stdint.h>
typedef struct
{
    uint32_t Data;
} Verilation;
volatile Verilation *const verilation = (Verilation *)0x60003800;

uint32_t verilation_read()
{
    return verilation->Data;
}

void verilation_write(uint32_t word)
{
    verilation->Data = word;
}