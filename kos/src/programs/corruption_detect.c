#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../uart.h"

const bool BUSY_WAIT = false;
void corruption_detect_test()
{
    // loop over 1000-9999 and ensure it renders the correct number of digits
    // using snprintf. loop repeated forever.
    char buf[10];
    while (1)
    {
        _write(1, ".", 1);
        for (int i = 1000; i < 10000; i++)
        {
            snprintf(buf, 10, "%d", i);
            buf[9] = '\0'; // ensure null termination even if corruption occurs

            _write(1, "`", 1);
            _write(1, buf, strlen(buf));
            _write(1, "`\n", 2);

            if (strlen(buf) != 4)
            {
                _write(1, "corruption detected!\n", 21);
                while (BUSY_WAIT)
                    ;
            }
        }
    }
}

// Minimalistic snprintf-like function for integers ranging from 1000-9999.
void simple_itoa(int num, char *buf)
{
    for (int i = 3; i >= 0; i--)
    {
        buf[i] = (num % 10) + '0';
        num /= 10;
    }
    buf[4] = '\0';
}

void corruption_detect_test2()
{
    char buf[10];

    while (1)
    {
        _write(1, ".", 1);

        for (int i = 1000; i < 10000; i++)
        {
            simple_itoa(i, buf); // Use our minimal version

            if (strlen(buf) != 4)
            {
                _write(1, "corruption detected!\n", 21);
                while (BUSY_WAIT)
                    ;
            }
        }
    }
}
void simple_memmove(char *dest, const char *src, size_t n)
{
    if (dest < src || dest >= (src + n))
    {
        while (n--)
        {
            *dest++ = *src++;
        }
    }
    else
    {
        dest += n;
        src += n;
        while (n--)
        {
            *(--dest) = *(--src);
        }
    }
}
void corruption_detect_test3()
{
    char buf[10];
    char temp[10];

    while (1)
    {
        _write(1, ".", 1);

        for (int i = 1000; i < 10000; i++)
        {
            // itoa(i, temp);         // Use our minimal version to a temp buffer
            __itoa(i, temp, 10);   // Use the libc version to a temp buffer
            memmove(buf, temp, 5); // simulate memmove operation

            _write(1, "`", 1);
            _write(1, buf, strlen(buf));
            _write(1, "`\n", 2);

            if (strlen(buf) != 4)
            {
                _write(1, "corruption detected!\n", 21);
                while (BUSY_WAIT)
                    ;
            }
        }
    }
}
void corruption_detect_test4()
{
    char *buf;
    int alloc_size = 10;
    char test_data[] = "test1234";

    while (1)
    {
        _write(1, ".", 1);

        buf = (char *)malloc(alloc_size);
        if (!buf)
        {
            _write(1, "allocation failed!\n", 19);
            while (BUSY_WAIT)
                ;
        }

        strncpy(buf, test_data, alloc_size);
        buf[alloc_size - 1] = '\0'; // Ensure null termination

        if (strcmp(buf, test_data) != 0)
        {
            _write(1, "corruption detected in malloc!\n", 31);
            while (BUSY_WAIT)
                ;
        }

        free(buf);
    }
}
void corruption_detect_test5()
{
    // disable_timer();
    volatile double value1 = 123.456;
    volatile double result;
    volatile double result2;

    while (1)
    {

        for (int i = 1000; i < 1500; i++)
        {
            _write(1, ".", 1);
            // addition
            result = value1 + (double)i;
            result2 = value1 + (double)i;
            // asm("li a7, 5");
            // asm volatile("ecall");
            if (result2 != result)
            {
                _write(1, "corruption detected in floating point addition!\n", 49);
                while (BUSY_WAIT)
                    ;
            }

            // subtraction
            result = value1 - (double)i;
            result2 = value1 - (double)i;
            if (result2 != result)
            {
                _write(1, "corruption detected in floating point subtraction!\n", 52);
                while (BUSY_WAIT)
                    ;
            }

            // multiplication
            result = value1 * (double)i;
            result2 = value1 * (double)i;
            if (result2 != result)
            {
                _write(1, "corruption detected in floating point multiplication!\n", 54);
                while (BUSY_WAIT)
                    ;
            }

            // division
            result = value1 / (double)i;
            result2 = value1 / (double)i;
            if (result2 != result)
            {
                _write(1, "corruption detected in floating point divide!\n", 45);
                while (BUSY_WAIT)
                    ;
            }
        }
    }
}
