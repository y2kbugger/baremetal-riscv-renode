#include "../baremetal.h"
#include "../verilation.h"
#include "../uart.h"

uint32_t read_hex_double_word()
{
    puts("Enter a 32-bit hex number: 0x");
    uint32_t value = 0;
    int count = 0;
    while (count < 8)
    { // A 32-bit hex number is up to 8 characters long
        int ch = getc();

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
            puts("Invalid character encountered.");
            return 0; // Or any other error handling mechanism
        }
        putc(ch);

        count++;
    }
    putc('\n');
    return value;
}

void ver_test()
{
    verilation_test();
    end_this_process();
}

// void ver_write()
// {
//     uint32_t n = read_hex_double_word();
//     verilation_write(n);
//     puts("Wrote hex to verilated reg\n");
//     end_this_process();
// }
// void ver_read()
// {
//     uint32_t n = verilation_read();
//     print_hex(n);
//     putc('\n');
//     end_this_process();
// }
// void ver_write2()
// {
//     uint32_t n = read_hex_double_word();
//     verilation_write2(n);
//     puts("Wrote hex to verilated reg\n");
//     end_this_process();
// }
// void ver_read2()
// {
//     uint32_t n = verilation_read2();
//     print_hex(n);
//     putc('\n');
//     end_this_process();
// }