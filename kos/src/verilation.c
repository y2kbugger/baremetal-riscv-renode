#include <stdint.h>
#include <stdbool.h>
#include "uart.h"
#include "hex.h"

typedef struct
{
    uint8_t A[3][3];
    uint8_t B[3][3];
    uint8_t C[3][3];
} MatMul;
volatile MatMul *const matmul = (MatMul *)0x60003800;

void print_matrix(char label[], uint8_t matrix[3][3])
{
    putc('\n');
    puts(label);
    putc('\n');
    for (int i = 0; i < 3; i++)
    {
        puts("| ");
        for (int j = 0; j < 3; j++)
        {
            print_hex(matrix[i][j], 1);
            putc(' ');
        }
        puts("|\n");
    }
}

void read_matrix(char label[], uint8_t matrix[3][3])
{
    puts("Input a 3x3 matrix of hex values for matrix ");
    puts(label);
    puts(":\n");
    for (int i = 0; i < 3; i++)
    {
        puts("| ");
        for (int j = 0; j < 3; j++)
        {
            int8_t value = (int8_t)read_hex(1);
            matrix[i][j] = value;
            putc(' ');
        }
        puts("|\n");
    }
}

void software_matrix_multiply(uint8_t a[3][3], uint8_t b[3][3], uint8_t c[3][3])
{
    // Manually multiply the matrices in software
    // This is the same algorithm as in the verilated hardware
    // You can use this to verify that the hardware is working correctly
    for (int i = 0; i < 3; i++)
    {
        uint8_t row[3] = {a[i][0], a[i][1], a[i][2]};
        for (int j = 0; j < 3; j++)
        {
            uint8_t col[3] = {b[0][j], b[1][j], b[2][j]};
            uint8_t sum = 0;
            for (int k = 0; k < 3; k++)
            {
                sum += row[k] * col[k];
            }
            c[i][j] = sum;
        }
    }
}

void check_matrix_multiply(uint8_t a[3][3], uint8_t b[3][3])
{
    uint8_t expected_c[3][3] = {};
    software_matrix_multiply(a, b, expected_c);
    print_matrix("Expected C", expected_c);

    // Copy matrices to the MatMul hardware
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matmul->A[i][j] = a[i][j];
            matmul->B[i][j] = b[i][j];
        }
    }

    // Read the result from the MatMul hardware
    uint8_t actual_c_values[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            actual_c_values[i][j] = matmul->C[i][j];
        }
    }
    print_matrix("Actual C", actual_c_values);

    bool is_correct = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (actual_c_values[i][j] != expected_c[i][j])
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
}