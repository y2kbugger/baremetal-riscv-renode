#include <stdio.h>

#include "../baremetal.h"

void count_forever()
{
    char count = '0';
    while (1)
    {
        putchar(count++);
        if (count == '9')
            count = '0';
    }
}
