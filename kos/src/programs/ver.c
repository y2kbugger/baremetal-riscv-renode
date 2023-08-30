#include "../baremetal.h"
#include "../verilation.h"
#include "../uart.h"

void ver_test()
{
    verilation_test();
    end_this_process();
}
