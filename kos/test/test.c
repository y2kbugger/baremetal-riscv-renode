#include <stdio.h>
#include "../src/circularbuffer.test.h"

int main()
{
    test_empty_buffer();
    test_full_buffer();
    test_write_to_buffer();
    test_read_from_buffer();
    test_read_from_empty_buffer();
    test_wrap_around();
    printf("All tests passed!\n");
    return 0;
}