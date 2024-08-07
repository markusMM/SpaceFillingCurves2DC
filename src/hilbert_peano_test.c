#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "helpers_2d.h"
#include "hilbert_peano.h"
#include <gsl/gsl_matrix.h>

// Function to compare two matrices
int compare_matrices(const gsl_matrix *m1, const gsl_matrix *m2) {
    if (m1->size1 != m2->size1 || m1->size2 != m2->size2) {
        return 0;
    }

    for (size_t i = 0; i < m1->size1; ++i) {
        for (size_t j = 0; j < m1->size2; ++j) {
            if (gsl_matrix_get(m1, i, j) != gsl_matrix_get(m2, i, j)) {
                return 0;
            }
        }
    }

    return 1;
}

// Test function for a specific example
void test_specific_example(int d, const int *expected_values, int verbose) {
    gsl_matrix *map = hilbert_peano(d, verbose, 0);

    gsl_matrix *expected = gsl_matrix_alloc(d, d);
    for (size_t i = 0; i < d; ++i) {
        for (size_t j = 0; j < d; ++j) {
            gsl_matrix_set(expected, i, j, expected_values[i * d + j]);
        }
    }

    if (verbose) {
        printf("Generated map for dimension %d:\n", d);
        print_matrix(map);

        printf("Expected map for dimension %d:\n", d);
        print_matrix(expected);
    }

    int match = compare_matrices(map, expected);
    assert(match);

    gsl_matrix_free(map);
    gsl_matrix_free(expected);
}

// Test function for Hilbert-Peano curves
void test_entry_exit(int d, int verbose) {
    gsl_matrix *map = hilbert_peano(d, verbose, 0);

    // Verify start at bottom left
    int start_value = gsl_matrix_get(map, d - 1, 0);
    assert(start_value == 0);

    // Verify end position based on curve type
    int hil = (int)(d % 2 == 0 || d == 2);
    int end_value;
    if (hil) {
        end_value = gsl_matrix_get(map, d - 1, d - 1);
    } else {
        end_value = gsl_matrix_get(map, 0, d - 1);
    }
    assert(end_value == (d * d) - 1);

    if (verbose) {
        printf("Map for dimension %d:\n", d);
        print_matrix(map);
    }

    gsl_matrix_free(map);
}

int main() {
    // Test a specific example
    int verbose = 0, d;

    // Example for a 2x2 Hilbert curve
    d = 2;
    int expected2[2*2] = {
        1, 2,
        0, 3
    };
    printf("Testing specific example for dimension %d:\n", d);
    test_specific_example(d, expected2, verbose);

    // Example for a 3x3 Peano curve
    d = 3;
    int expected3[3*3] = {
        6, 7, 8,
        5, 4, 3,
        0, 1, 2
    };
    printf("Testing specific example for dimension %d:\n", d);
    test_specific_example(d, expected3, verbose);

    // Example for a 4x4 Peano curve
    d = 4;
    int expected4[4*4] = {
        5,    6,    9,   10,
        4,    7,    8,   11,
        3,    2,   13,   12,
        0,    1,   14,   15
    };
    printf("Testing specific example for dimension %d:\n", d);
    test_specific_example(d, expected4, verbose);

    // Example for a 6x6 Peano curve
    d = 6;
    int expected6[6*6] = {
        11, 12, 13, 22, 23, 24,
        10, 15, 14, 21, 20, 25,
         9, 16, 17, 18, 19, 26,
         8,  7,  6, 29, 28, 27,
         1,  2,  5, 30, 33, 34,
         0,  3,  4, 31, 32, 35
    };
    printf("Testing specific example for dimension %d:\n", d);
    test_specific_example(d, expected6, verbose);

    // Example for a 8x8 Peano curve
    d = 8;
    int expected8[8*8] = {
        21, 22, 25, 26, 37, 38, 41, 42,
        20, 23, 24, 27, 36, 39, 40, 43,
        19, 18, 29, 28, 35, 34, 45, 44,
        16, 17, 30, 31, 32, 33, 46, 47,
        15, 12, 11, 10, 53, 52, 51, 48,
        14, 13,  8,  9, 54, 55, 50, 49,
         1,  2,  7,  6, 57, 56, 61, 62,
         0,  3,  4,  5, 58, 59, 60, 63
    };
    printf("Testing specific example for dimension %d:\n", d);
    test_specific_example(d, expected8, verbose);

    // Example for a 12x12 Peano curve
    d = 12;
    int expected12[12*12] = {
        47,  48,  49,  58,  59,  60,  83,  84,  85,  94,  95,  96,
        46,  51,  50,  57,  56,  61,  82,  87,  86,  93,  92,  97,
        45,  52,  53,  54,  55,  62,  81,  88,  89,  90,  91,  98,
        44,  43,  42,  65,  64,  63,  80,  79,  78, 101, 100,  99,
        37,  38,  41,  66,  69,  70,  73,  74,  77, 102, 105, 106,
        36,  39,  40,  67,  68,  71,  72,  75,  76, 103, 104, 107,
        35,  34,  27,  26,  25,  24, 119, 118, 117, 116, 109, 108,
        32,  33,  28,  19,  20,  23, 120, 123, 124, 115, 110, 111,
        31,  30,  29,  18,  21,  22, 121, 122, 125, 114, 113, 112,
         4,   5,   6,  17,  14,  13, 130, 129, 126, 137, 138, 139,
         3,   2,   7,  16,  15,  12, 131, 128, 127, 136, 141, 140,
         0,   1,   8,   9,  10,  11, 132, 133, 134, 135, 142, 143
    };
    printf("Testing specific example for dimension %d:\n", d);
    test_specific_example(d, expected12, verbose);

    // Add more specific examples as needed
    // ...

    printf("All specific example tests passed!\n");

    printf("Testing entrance and exit!\n");

    // Test for Hilbert curves (dimensions 2, 4, 6, ...)
    for (int d = 2; d <= 6; d += 2) {
        printf("Testing Hilbert curve with dimension %d:\n", d);
        test_entry_exit(d, verbose);
    }

    // Test for Peano curves (dimensions 3, 9, ...)
    for (int d = 3; d <= 9; d += 3) {
        printf("Testing Peano curve with dimension %d:\n", d);
        test_entry_exit(d, verbose);
    }

    printf("All entry-exit tests passed!\n");

    return 0;
}
