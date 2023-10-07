#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#define BUFFER_SIZE 256

struct circular_buffer
{
    char data[BUFFER_SIZE];
    int read_index;
    int write_index;
};

int is_buffer_empty(struct circular_buffer *buffer);
int is_buffer_full(struct circular_buffer *buffer);
void write_to_buffer(struct circular_buffer *buffer, char value);
char read_from_buffer(struct circular_buffer *buffer);

#endif /* CIRCULARBUFFER_H */