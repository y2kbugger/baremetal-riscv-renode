#include "../baremetal.h"
#include "../uart.h"

void helloworld()
{
    puts("Hello World");
    end_this_process();
}
