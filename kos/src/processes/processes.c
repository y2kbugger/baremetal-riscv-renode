#include "../process.h"

#include "helloworld.h"
#include "lol.h"
#include "monitor.h"

void init_all_processes()
{
    add_process('h', helloworld);
    add_process('l', lol);
    add_process('m', monitor);
}
