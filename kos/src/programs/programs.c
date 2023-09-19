#include "../process.h"

#include "helloworld.h"
#include "lol.h"
#include "count.h"
#include "shell.h"
#include "ver.h"
#include "corruption_detect.h"

void register_all_programs()
{
    register_program('h', helloworld);
    register_program('e', hello_ecall_world);
    register_program('l', lol);
    register_program('f', laugh_forever);
    register_program('c', count_forever);

    register_program('v', ver_test);
    register_program('q', corruption_detect_test5);
    register_program('m', multiply_matrices);

    register_program('s', shell);
}
