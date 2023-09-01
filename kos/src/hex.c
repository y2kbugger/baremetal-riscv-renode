#include <stdint.h>
#include <stdio.h>

void print_hex(uint32_t value, int bytes)
{
    // Define hex characters
    const char hex_chars[] = "0123456789ABCDEF";

    // Process each 4-bit chunk (nibble)
    for (int shift = bytes * 8 - 4; shift >= 0; shift -= 4)
    {
        char hex_char = hex_chars[(value >> shift) & 0xF];
        putchar(hex_char);
    }
}

uint32_t read_hex(int bytes)
{
    // max of 4 bytes
    // echo valid hex characters
    uint32_t value = 0;
    int count = 0;
    while (count < bytes * 2)
    {
        int ch = getchar();

        // Convert hex char to integer
        if (ch >= '0' && ch <= '9')
        {
            value = (value << 4) | (ch - '0');
        }
        else if (ch >= 'a' && ch <= 'f')
        {
            value = (value << 4) | (ch - 'a' + 10);
        }
        else if (ch >= 'A' && ch <= 'F')
        {
            value = (value << 4) | (ch - 'A' + 10);
        }
        else
        {
            // skip non-hex characters
            continue;
        }
        putchar(ch);

        count++;
    }
    return value;
}