#include "../process.h"

#include "helloworld.h"
#include "lol.h"
#include "count.h"
#include "monitor.h"

void register_all_programs()
{
    register_program('h', helloworld);
    register_program('l', lol);
    register_program('f', laugh_forever);
    register_program('c', count_forever);
    register_program('m', monitor);
}
