#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hilbert_peano.h"
#include "helpers_2d.h"

int main() {
    int d = 9;
    int verbose = 1;
    int sub = 0;

    printf("Welcome to the 2D space filling curves!\n");
    printf("This is a demo outputting a 2D map of the indices.\n");
    printf("But caution, those functions currently only support 2^n and 3^n elements sqare areas!\n");
    printf("And keep in mind that large matrices couldn't be displayed here!\n");
    printf("Please input you desired side length: ");
    scanf(" %d", &d);

    // final recursive mapper function
    gsl_matrix *map = hilbert_peano(d, verbose, sub);

    printf("Hilbert-Peano map:\n");
    print_matrix(map);

    gsl_matrix_free(map);
    return 0;
}
