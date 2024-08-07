#ifndef HILBERT_PEANO_H
#define HILBERT_PEANO_H

#include <gsl/gsl_matrix.h>

// Main Hilbert-Peano function declaration
gsl_matrix* hilbert_peano(int d, int verbose, int sub);
void hilbert_peano_(gsl_matrix* map, int d, int verbose, int sub);
void create_base_matrix(gsl_matrix* base, int hil, int sub);

#endif // HILBERT_PEANO_H