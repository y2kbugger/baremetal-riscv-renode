#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "hex.h"

typedef struct
{
    uint8_t A[3][3];
    uint8_t B[3][3];
    uint8_t C[3][3];
} MatMul;
volatile MatMul *const matmul = (MatMul *)0x60003800;

void hardware_matrix_multiply_3(uint8_t a[3][3], uint8_t b[3][3], uint8_t c[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            matmul->A[i][j] = a[i][j];
            matmul->B[i][j] = b[i][j];
        }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            c[i][j] = matmul->C[i][j];
}

void hardware_matrix_multiply_3(uint8_t a[3][3], uint8_t b[3][3], uint8_t c[3][3]);

void print_matrix(char label[], uint8_t matrix[3][3])
{
    printf("\n%s\n", label);

    for (int i = 0; i < 3; i++)
    {
        printf("| ");
        for (int j = 0; j < 3; j++)
        {
            print_hex(matrix[i][j], 1);
            putchar(' ');
        }
        printf("|\n");
    }
}

void print_matrix_9(char label[], uint8_t matrix[9][9])
{
    printf("\n%s\n", label);
    for (int i = 0; i < 9; i++)
    {
        printf("| ");
        for (int j = 0; j < 9; j++)
        {
            print_hex(matrix[i][j], 1);
            putchar(' ');
        }
        printf("|\n");
    }
}

void read_matrix(char label[], uint8_t matrix[3][3])
{
    printf("Input a 3x3 matrix of hex values for matrix %s\n", label);
    for (int i = 0; i < 3; i++)
    {
        printf("| ");
        for (int j = 0; j < 3; j++)
        {
            int8_t value = (int8_t)read_hex(1);
            matrix[i][j] = value;
            putchar(' ');
        }
        printf("|\n");
    }
}

void software_matrix_multiply(uint8_t a[3][3], uint8_t b[3][3], uint8_t c[3][3])
{
    // Manually multiply the matrices in software
    // This is the same algorithm as in the verilated hardware
    // You can use this to verify that the hardware is working correctly
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            uint8_t sum = 0;
            for (int k = 0; k < 3; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}

void software_matrix_multiply_9(uint8_t a[9][9], uint8_t b[9][9], uint8_t c[9][9])
{
    // Manually multiply the matrices in software
    // This is the same algorithm as in the verilated hardware
    // You can use this to verify that the hardware is working correctly
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            uint8_t sum = 0;
            for (int k = 0; k < 9; k++)
            {
                sum += a[i][k] * b[k][j];
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

    uint8_t actual_c_values[3][3];
    hardware_matrix_multiply_3(a, b, actual_c_values);
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
        printf("Matrix multiplication result is correct!\n");
    }
    else
    {
        printf("Matrix multiplication result is incorrect!\n");
    }
}

void check_matrix_multiply_9(uint8_t a[9][9], uint8_t b[9][9])
{
    uint8_t expected_c[9][9] = {};
    software_matrix_multiply_9(a, b, expected_c);
    print_matrix_9("Expected C", expected_c);

    uint8_t actual_c_values[9][9] = {};

    for (int block_row = 0; block_row < 3; block_row++)
    {
        for (int block_col = 0; block_col < 3; block_col++)
        {
            for (int k = 0; k < 3; k++)
            {
                uint8_t subA[3][3], subB[3][3], subC[3][3] = {};

                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        subA[i][j] = a[3 * block_row + i][3 * k + j]; // Modified to use k
                        subB[i][j] = b[3 * k + i][3 * block_col + j]; // Modified to use k and block_col
                    }
                }

                hardware_matrix_multiply_3(subA, subB, subC);

                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        actual_c_values[3 * block_row + i][3 * block_col + j] += subC[i][j];
                    }
                }
            }
        }
    }

    print_matrix_9("Actual C", actual_c_values);

    bool is_correct = true;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
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
        printf("Matrix multiplication result is correct!\n");
    }
    else
    {
        printf("Matrix multiplication result is incorrect!\n");
    }
}
