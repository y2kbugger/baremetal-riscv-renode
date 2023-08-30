#include <stdint.h>
typedef struct
{
    uint32_t Data;
    // uint32_t Datax;
    // uint32_t Data7;
    // uint32_t Data7a;
    // uint32_t Data7ab;
    uint32_t Data2;
} Verilation;
volatile Verilation *const verilation = (Verilation *)0x60003800;

uint32_t verilation_read()
{
    return verilation->Data;
}
uint32_t verilation_read2()
{
    return verilation->Data2;
}

void verilation_write(uint32_t word)
{
    verilation->Data = word;
}
void verilation_write2(uint32_t word)
{
    verilation->Data2 = word;
}