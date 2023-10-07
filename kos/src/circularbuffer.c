#include "circularbuffer.h"

int is_buffer_empty(struct circular_buffer *buffer)
{
    return buffer->read_index == buffer->write_index;
}

int is_buffer_full(struct circular_buffer *buffer)
{
    return (buffer->write_index + 1) % BUFFER_SIZE == buffer->read_index;
}

void write_to_buffer(struct circular_buffer *buffer, char value)
{
    if (!is_buffer_full(buffer))
    {
        buffer->data[buffer->write_index] = value;
        buffer->write_index = (buffer->write_index + 1) % BUFFER_SIZE;
    }
    // If buffer is full, we drop new data.
}

char read_from_buffer(struct circular_buffer *buffer)
{
    char value = 0;
    if (!is_buffer_empty(buffer))
    {
        value = buffer->data[buffer->read_index];
        buffer->read_index = (buffer->read_index + 1) % BUFFER_SIZE;
    }
    return value; // If buffer is empty, this will return 0 or '\0'. Handle accordingly.
}