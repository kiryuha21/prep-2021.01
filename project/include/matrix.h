#ifndef UNTITLED2_MATRIX_H
#define UNTITLED2_MATRIX_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define DET_ERR (-1)

typedef struct Matrix {
    double** matrix;
    size_t rows;
    size_t cols;
} Matrix;

// support functions

int swap_rows(Matrix* matrix, size_t first, size_t second);

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
int free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* cols);
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);

//Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);
Matrix* transp(const Matrix* matrix);

Matrix* sum(const Matrix* l, const Matrix* r);
Matrix* sub(const Matrix* l, const Matrix* r);
Matrix* mul(const Matrix* l, const Matrix* r);

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);

#endif //UNTITLED2_MATRIX_H
