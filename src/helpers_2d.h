#ifndef HELPERS_2D_H
#define HELPERS_2D_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_matrix.h>

// Helper function declarations
void prime_factors(int n, int* factors, int* count);
int prime_check(int n);

// print function
void print_matrix(gsl_matrix* mat);
// flip matrices
void flip_matrix_horizontal(gsl_matrix* mat);
void flip_matrix_vertical(gsl_matrix* mat);
void find_indices(const gsl_matrix* mat, double value, size_t* ind_x, size_t* ind_y);

#endif // HELPERS_2D_H