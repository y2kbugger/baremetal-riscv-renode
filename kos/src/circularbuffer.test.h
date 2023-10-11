#include <assert.h>
#include <stdio.h>
#include "circularbuffer.h"
#include "circularbuffer.c"

void test_empty_buffer()
{
    struct circular_buffer buffer =
        {
            .read_index = 0,
            .write_index = 0,
        };
    assert(is_buffer_empty(&buffer));
}

void test_full_buffer()
{
    struct circular_buffer buffer =
        {
            .read_index = 0,
            .write_index = BUFFER_SIZE - 1,
        };
    assert(is_buffer_full(&buffer));
}

void test_write_to_buffer()
{
    struct circular_buffer buffer =
        {
            .data = {},
            .read_index = 0,
            .write_index = 0,
        };
    write_to_buffer(&buffer, 'a');
    assert(buffer.data[0] == 'a');
    assert(buffer.write_index == 1);
}

void test_read_from_buffer()
{
    struct circular_buffer buffer =
        {
            .data = {'a', 'b', 'c'},
            .read_index = 0,
            .write_index = 3,
        };
    assert(!is_buffer_empty(&buffer));
    assert(buffer.read_index == 0);
    char value = read_from_buffer(&buffer);
    assert(value == 'a');
    assert(buffer.read_index == 1);
}

void test_read_from_empty_buffer()
{
    struct circular_buffer buffer =
        {
            .data = {},
            .read_index = 0,
            .write_index = 0,
        };
    assert(is_buffer_empty(&buffer));
    assert(buffer.read_index == 0);
    char value = read_from_buffer(&buffer);
    assert(value == 0);
    assert(buffer.read_index == 0);
}

void test_wrap_around()
{
    struct circular_buffer buffer =
        {
            .read_index = 0,
            .write_index = BUFFER_SIZE - 1,
        };

    assert(is_buffer_full(&buffer));
    assert(buffer.write_index == BUFFER_SIZE - 1);
    read_from_buffer(&buffer);
    read_from_buffer(&buffer);
    assert(!is_buffer_full(&buffer));
    write_to_buffer(&buffer, 'z');
    write_to_buffer(&buffer, 'z');
    assert(is_buffer_full(&buffer));
    assert(buffer.write_index == 1);
    assert(buffer.read_index == 2);
}
