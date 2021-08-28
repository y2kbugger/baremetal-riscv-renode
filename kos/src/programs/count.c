#include "../baremetal.h"
#include "../uart.h"

void count_forever()
{
    char count = '0';
    while (1)
    {
        putc(count++);
        if (count == '9')
            count = '0';
    }
}
