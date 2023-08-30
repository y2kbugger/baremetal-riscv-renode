#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t A[3][3];
    uint8_t B[3][3];
    uint8_t C[3][3];
} MatMul;
volatile MatMul *const matmul = (MatMul *)0x60003800;

int verilation_test()
{
    // Setting matrix A
    uint8_t a_values[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}};

    // Setting matrix B
    uint8_t b_values[3][3] = {
        {1, 9, 8},
        {7, 6, 5},
        {4, 3, 2}};

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

    bool is_correct = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matmul->C[i][j] != expected_c_values[i][j])
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
