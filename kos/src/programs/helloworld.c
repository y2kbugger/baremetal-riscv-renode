#include "../baremetal.h"
#include "../uart.h"

void helloworld()
{
    puts("Hello World");
    end_this_process();
}

void hello_ecall_world()
{
    puts("Hello");
    asm("li a7, 5");
    asm volatile("ecall");
    puts("World");
    end_this_process();
}
