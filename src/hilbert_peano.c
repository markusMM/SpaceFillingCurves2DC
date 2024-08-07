#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gsl/gsl_matrix.h>
#include "hilbert_peano.h"
#include "helpers_2d.h"

void create_base_matrix(gsl_matrix* base, int hil, int sub) {
    if (hil) {
        gsl_matrix_set(base, 0, 0, 1);
        gsl_matrix_set(base, 0, 1, 0);
        gsl_matrix_set(base, 1, 0, 2);
        gsl_matrix_set(base, 1, 1, 3);
        gsl_matrix_transpose(base);
    } else {
        if (sub) {
            gsl_matrix_set(base, 0, 0, 4);
            gsl_matrix_set(base, 0, 1, 5);
            gsl_matrix_set(base, 0, 2, 6);
            gsl_matrix_set(base, 1, 0, 3);
            gsl_matrix_set(base, 1, 1, 2);
            gsl_matrix_set(base, 1, 2, 7);
            gsl_matrix_set(base, 2, 0, 0);
            gsl_matrix_set(base, 2, 1, 1);
            gsl_matrix_set(base, 2, 2, 8);
        } else {
            gsl_matrix_set(base, 0, 0, 0);
            gsl_matrix_set(base, 0, 1, 5);
            gsl_matrix_set(base, 0, 2, 6);
            gsl_matrix_set(base, 1, 0, 1);
            gsl_matrix_set(base, 1, 1, 4);
            gsl_matrix_set(base, 1, 2, 7);
            gsl_matrix_set(base, 2, 0, 2);
            gsl_matrix_set(base, 2, 1, 3);
            gsl_matrix_set(base, 2, 2, 8);
            // flip_matrix_horizontal(base);
            gsl_matrix_transpose(base);
            flip_matrix_vertical(base);
        }
    }
}

void hilbert_peano_(gsl_matrix* map, int d, int verbose, int sub) {
    if (d <= 0) {
        fprintf(stderr, "Dimension must be a positive integer\n");
        return;
    }

    int hil = (int)(d % 2 == 0 || d == 2);
    int diff = (int)floor(d / (3 - hil));
    int hm3 = (int)(diff % 2 == 0);
    int d_base = hil ? 2 : 3;

    gsl_matrix* base = gsl_matrix_alloc(d_base, d_base);
    create_base_matrix(base, hil, sub);

    if (d == 2 || d == 3) {
        gsl_matrix_memcpy(map, base);
    } else {
        for (int r = 0; r < (int)(base->size1 * base->size2); r++) {
            gsl_matrix* sub_map = gsl_matrix_alloc(diff, diff);
            hilbert_peano_(sub_map, diff, verbose, hil && !hm3 || sub);

            if (!hm3 && hil && ((r + 1) % 2 == 0)) {
                double smax = gsl_matrix_max(sub_map);
                gsl_matrix_scale(sub_map, -1);
                gsl_matrix_add_constant(sub_map, smax);
                flip_matrix_horizontal(sub_map);
            }

            if (hil) {
                if (r == 0) {
                    flip_matrix_horizontal(sub_map);
                    gsl_matrix_transpose(sub_map);
                    flip_matrix_horizontal(sub_map);
                }
                if (r == 3) {
                    gsl_matrix_transpose(sub_map);
                }
            } else {
                if ((r + 1) % 2 == 0) {
                    flip_matrix_vertical(sub_map);
                }
                if (r >= 3 && r < 6) {
                    flip_matrix_vertical(sub_map);
                    flip_matrix_horizontal(sub_map);
                }
            }

            size_t ind_x = 0, ind_y = 0;
            find_indices(base, r, &ind_x, &ind_y);

            if (verbose) {
                printf("sub-map:\n");
                print_matrix(sub_map);
                printf("\n");
                printf("bas-pos: (%zu, %zu)\n", ind_x, ind_y);
            }

            ind_x *= diff;
            ind_y *= diff;

            if (verbose) {
                printf("pos-fac: %d\n", diff);
                printf("fac-pos: (%zu, %zu)\n", ind_x, ind_y);
            }

            for (size_t i = 0; i < sub_map->size1; i++) {
                for (size_t j = 0; j < sub_map->size2; j++) {
                    if ((ind_x + i) < map->size1 && (ind_y + j) < map->size2) {
                        gsl_matrix_set(
                            map,
                            ind_x + i,
                            ind_y + j,
                            gsl_matrix_get(sub_map, i, j) + (double) (r * diff * diff)
                        );
                    } else {
                        fprintf(stderr, "Index out of bounds: (%zu, %zu)\n", ind_x + i, ind_y + j);
                    }
                }
            }

            gsl_matrix_free(sub_map);
        }
    }

    gsl_matrix_free(base);
}

gsl_matrix* hilbert_peano(int d, int verbose, int sub) {
    assert(prime_check(d));
    gsl_matrix* map = gsl_matrix_alloc(d, d);
    hilbert_peano_(map, d, verbose, sub);
    return map;
}
