#include "../baremetal.h"
#include "../verilation.h"
#include "../uart.h"

void ver_test()
{
    // Setting matrix A
    uint8_t a[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}};
    print_matrix("A", a);

    // Setting matrix B
    uint8_t b[3][3] = {
        {1, 9, 8},
        {7, 6, 5},
        {4, 3, 2}};
    print_matrix("B", b);

    for (int k = 0; k < 3; k++)
    {
        // Generate multiple test cases
        b[0][0] += k;
        check_matrix_multiply(a, b);
    }
    end_this_process();
}

void multiply_matrices()
{
    uint8_t a[3][3] = {};
    uint8_t b[3][3] = {};

    read_matrix("A", a);
    read_matrix("B", b);

    check_matrix_multiply(a, b);
    end_this_process();
}
