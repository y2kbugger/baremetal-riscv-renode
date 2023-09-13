#include <stdio.h>

#include "../baremetal.h"

void helloworld()
{
    printf("Hello World\n");
    end_this_process();
}

void hello_ecall_world()
{
    printf("Hello");
    fflush(stdout);

    asm("li a7, 5");
    asm volatile("ecall");

    printf("World\n");
    end_this_process();
}
