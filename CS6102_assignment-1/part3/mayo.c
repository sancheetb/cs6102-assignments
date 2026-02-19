#include "mayo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const unsigned char lookup_table[256] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 2, 4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13, 0, 3, 6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2, 0, 4, 8, 12, 3, 7, 11, 15, 6, 2, 14, 10, 5, 1, 13, 9, 0, 5, 10, 15, 7, 2, 13, 8, 14, 11, 4, 1, 9, 12, 3, 6, 0, 6, 12, 10, 11, 13, 7, 1, 5, 3, 9, 15, 14, 8, 2, 4, 0, 7, 14, 9, 15, 8, 1, 6, 13, 10, 3, 4, 2, 5, 12, 11, 0, 8, 3, 11, 6, 14, 5, 13, 12, 4, 15, 7, 10, 2, 9, 1, 0, 9, 1, 8, 2, 11, 3, 10, 4, 13, 5, 12, 6, 15, 7, 14, 0, 10, 7, 13, 14, 4, 9, 3, 15, 5, 8, 2, 1, 11, 6, 12, 0, 11, 5, 14, 10, 1, 15, 4, 7, 12, 2, 9, 13, 6, 8, 3, 0, 12, 11, 7, 5, 9, 14, 2, 10, 6, 1, 13, 15, 3, 4, 8, 0, 13, 9, 4, 1, 12, 8, 5, 2, 15, 11, 6, 3, 14, 10, 7, 0, 14, 15, 1, 13, 3, 2, 12, 9, 7, 6, 8, 4, 10, 11, 5, 0, 15, 13, 2, 9, 6, 4, 11, 1, 14, 12, 3, 8, 7, 5, 10};


extern void shake256(uint8_t *output, size_t output_len, 
                      const uint8_t *input, size_t input_len);

// Initialize a matrix with random GF(2^16) elements using SHAKE256
void init_random_matrix_p(uint16_t *matrix, int rows, int cols, 
                        const uint8_t *seed, size_t seed_len) {
    size_t num_elements = rows * cols;
    size_t num_bytes = num_elements * 2; 
    uint8_t random_bytes[2 * num_elements]; 
    
    shake256(random_bytes, num_bytes, seed, seed_len);
    
    for (size_t i = 0; i < num_elements; i++) {
        matrix[i] = (uint16_t)random_bytes[2*i] | 
                   ((uint16_t)random_bytes[2*i + 1] << 8);
    }
}

void init_random_matrix_o(uint16_t *matrix, int rows, int cols, 
                        const uint8_t *seed, size_t seed_len) {
    size_t num_elements = rows * cols;
    size_t num_bytes = num_elements * 2; 
    uint8_t *random_bytes[2 * num_elements];
    
    shake256(random_bytes, num_bytes, seed, seed_len);
    
    for (size_t i = 0; i < num_elements; i++) {
        matrix[i] = (uint16_t)random_bytes[2*i] | 
                   ((uint16_t)random_bytes[2*i + 1] << 8);
        matrix[i] %= 16;
    }
}

void init_random_matrix_l(uint16_t *matrix, int rows, int cols) {
    size_t num_elements = rows * cols;
    
    for (size_t i = 0; i < num_elements; i++) {

        matrix[i] = 0;
    }

}


// ============================================================================
// TODO : GF(2^16) Multiplication
// ============================================================================

uint16_t gf65536_mul(uint16_t a, uint16_t b) {
    // TODO STUDENTS: Implement GF(2^16) multiplication
	return lookup_table[(a << 4) | b];
}

// ============================================================================
// TODO : Matrix Operations
// ============================================================================

void gf65536_mat_transpose(const uint16_t *src, uint16_t *dst,
                           int rows, int cols) {
    // TODO STUDENTS: Implement matrix transpose
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			dst[j*rows + i] = src[i*cols + j];
		}
	}
}

void gf65536_mat_add(const uint16_t *A, const uint16_t *B, uint16_t *C,
                     int rows, int cols) {
    // TODO STUDENTS: Implement matrix addition over GF(2^16)
	for (int i = 0; i < rows*cols; i++) {
		C[i] = A[i] ^ B[i];
	}
}

/**
 * Matrix Multiplication
 * 
 * PERFORMANCE CRITICAL !!!
 * This is the bottleneck of the computation.
 * Make sure to optimize this function.
 */

void gf65536_mat_mul(const uint16_t *A, const uint16_t *B, uint16_t *C,
                     int rows_A, int cols_A, int cols_B) {
    // TODO STUDENTS: Implement matrix multiplication over GF(2^16)
	for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols_B; j++) {
            uint8_t sum = 0; 
            for (int k = 0; k < cols_A; k++) {
                // GF(2^4):   sum ^= gf16_mul(A[i][k], B[k][j])
                sum ^= gf65536_mul(A[i * cols_A + k], B[k * cols_B + j]);
            }
            C[i * cols_B + j] = sum;
        }
    }
}

// ============================================================================
// TODO: Compute L
// ============================================================================

/**
* Refer to parameters in mayo.h (these will be varied later so don't hard code the dimensions) 
* Matrix dimensions:
 * - P1: V × V (58 × 58) - upper triangular
 * - P2: V × O_PARAM (58 × 8)
 * - O:  V × O_PARAM (58 × 8)
 * - L:  V × O_PARAM (58 × 8)
 */
int compute_L(const uint16_t *P1, const uint16_t *P2,
               const uint16_t *O, uint16_t *L) {
    // TODO: Implement the L computation
	uint16_t P1_T[V * V];
    uint16_t P1_plus_P1T[V * V];
    uint16_t intermediate[V * O_PARAM];

    gf65536_mat_transpose(P1, P1_T, V, V);

    gf65536_mat_add(P1, P1_T, P1_plus_P1T, V, V);

    gf65536_mat_mul(P1_plus_P1T, O, intermediate, V, V, O_PARAM);

    gf65536_mat_add(intermediate, P2, L, V, O_PARAM);

    return 0;
}
