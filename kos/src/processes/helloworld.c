#include "../baremetal.h"
#include "../uart.h"

void helloworld()
{
    puts("Hello World\n");
    end_this_process();
}
