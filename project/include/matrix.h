#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define CREATE_ERR (-1)
#define GET_ERR    (-2)
#define SET_ERR    (-3)
#define DET_ERR    (-4)
#define TRANSP_ERR (-5)
#define SUM_ERR    (-6)
#define FREE_ERR   (-7)
#define SUB_ERR    (-8)
#define MUL_ERR    (-9)
#define INV_ERR    (-10)


typedef struct Matrix {
    double** matrix_content;
    size_t rows;
    size_t cols;
} Matrix;

// support functions
double recursive_det(double **origin_matrix, size_t m_size);
int minus_row_col(double **origin_matrix, double **temp_matrix, size_t row, size_t col, size_t m_size);
int free_matrix_content(double** matrix, size_t rows);

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
int free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* cols);
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);
Matrix* transp(const Matrix* matrix);

Matrix* sum(const Matrix* l, const Matrix* r);
Matrix* sub(const Matrix* l, const Matrix* r);
Matrix* mul(const Matrix* l, const Matrix* r);

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);

#endif  // PROJECT_INCLUDE_MATRIX_H_
