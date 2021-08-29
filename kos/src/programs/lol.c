#include "../baremetal.h"
#include "../uart.h"

void lol()
{
    puts("hahahahahahaha");
    end_this_process();
}

void laugh_forever()
{
    while (1)
        puts("ha");
}
