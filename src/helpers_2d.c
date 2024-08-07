#include "helpers_2d.h"

// Helper function to calculate prime factors
void prime_factors(int n, int* factors, int* count) {
    int i = 2;
    *count = 0;
    while (i * i <= n) {
        if (n % i == 0) {
            factors[(*count)++] = i;
            n /= i;
        } else {
            i += 1;
        }
    }
    if (n > 1) {
        factors[(*count)++] = n;
    }
}

// Helper function to check if all prime factors are not divisible by 2 or 3
int prime_check(int n) {
    int factors[100], count, i;
    prime_factors(n, factors, &count);
    for (i = 0; i < count; ++i) {
        if (factors[i] % 2 != 0 && factors[i] % 3 != 0) {
            printf("Dimension %dx%d not supported, as it cannot reduce to a 2x2 or 4x4 base!\n", n, n);
            return 0;
        }
    }
    return 1;
}

// print function
void print_matrix(gsl_matrix* mat) {
    for (size_t i = 0; i < mat->size1; i++) {
        for (size_t j = 0; j < mat->size2; j++) {
            printf("%4.0f ", gsl_matrix_get(mat, i, j));
        }
        printf("\n");
    }
}

void flip_matrix_horizontal(gsl_matrix* mat) {
    gsl_matrix* temp = gsl_matrix_alloc(mat->size1, mat->size2);
    for (size_t i = 0; i < mat->size1; i++) {
        for (size_t j = 0; j < mat->size2; j++) {
            gsl_matrix_set(temp, i, j, gsl_matrix_get(mat, i, mat->size2 - 1 - j));
        }
    }
    gsl_matrix_memcpy(mat, temp);
    gsl_matrix_free(temp);
}

void flip_matrix_vertical(gsl_matrix* mat) {
    gsl_matrix* temp = gsl_matrix_alloc(mat->size1, mat->size2);
    for (size_t i = 0; i < mat->size1; i++) {
        for (size_t j = 0; j < mat->size2; j++) {
            gsl_matrix_set(temp, i, j, gsl_matrix_get(mat, mat->size1 - 1 - i, j));
        }
    }
    gsl_matrix_memcpy(mat, temp);
    gsl_matrix_free(temp);
}

// Function to find the indices of a value in the matrix
void find_indices(const gsl_matrix* mat, double value, size_t* ind_x, size_t* ind_y) {
    for (size_t i = 0; i < mat->size1; ++i) {
        for (size_t j = 0; j < mat->size2; ++j) {
            if (gsl_matrix_get(mat, i, j) == value) {
                *ind_x = i;
                *ind_y = j;
                return;
            }
        }
    }
}
