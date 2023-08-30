#include <stdint.h>
#include <stdbool.h>
#include "uart.h"

typedef struct
{
    uint8_t A[3][3];
    uint8_t B[3][3];
    uint8_t C[3][3];
} MatMul;
volatile MatMul *const matmul = (MatMul *)0x60003800;

void print_matrix(char label[], uint8_t matrix[3][3])
{
    puts(label);
    putc('\n');
    for (int i = 0; i < 3; i++)
    {
        puts("| ");
        for (int j = 0; j < 3; j++)
        {
            print_hex(matrix[i][j], 8);
            putc(' ');
        }
        puts("|\n");
    }
}

int verilation_test()
{
    // Setting matrix A
    uint8_t a_values[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}};
    print_matrix("A", a_values);

    // Setting matrix B
    uint8_t b_values[3][3] = {
        {1, 9, 8},
        {7, 6, 5},
        {4, 3, 2}};
    print_matrix("B", b_values);

    // Copy matrices to the matmul structure
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matmul->A[i][j] = a_values[i][j];
            matmul->B[i][j] = b_values[i][j];
        }
    }

    // Start the multiplication
    // Depending on your architecture, you might need to set an 'Enable' flag.
    // Here, I'll assume the multiplication starts automatically when A and B are set.

    // After this, the result should be available in matmul->C
    // And you can further process or verify it as needed.
    // Example:
    uint8_t expected_c_values[3][3] = {
        {93, 150, 126},
        {57, 96, 81},
        {21, 42, 36}};
    print_matrix("Expected C", expected_c_values);

    uint8_t actual_c_values[3][3] = {
        {matmul->C[0][0], matmul->C[0][1], matmul->C[0][2]},
        {matmul->C[1][0], matmul->C[1][1], matmul->C[1][2]},
        {matmul->C[2][0], matmul->C[2][1], matmul->C[2][2]}};

    print_matrix("Actual C", actual_c_values);

    bool is_correct = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (actual_c_values[i][j] != expected_c_values[i][j])
            {
                is_correct = false;
                break;
            }
        }
        if (!is_correct)
        {
            break;
        }
    }

    if (is_correct)
    {
        // Matrix multiplication result is correct!
        puts("Matrix multiplication result is correct!\n");
    }
    else
    {
        puts("Matrix multiplication result is incorrect!\n");
    }

    return 0;
}
