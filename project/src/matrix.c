#include "matrix.h"

Matrix* create_matrix(size_t rows, size_t cols) {
    void* test_ptr_m = malloc(sizeof(struct Matrix));
    if (test_ptr_m == NULL) {
        return NULL;
    }

    Matrix* temp_matrix = (Matrix*)test_ptr_m;
    temp_matrix->rows = rows;
    temp_matrix->cols = cols;

    void** test_ptr_1 = (void**)malloc(rows * sizeof(double*));
    if (test_ptr_1 == NULL) {
        free(test_ptr_m);
        return NULL;
    }
    temp_matrix->matrix = (double**)test_ptr_1;

    for (size_t i = 0; i < rows; ++i) {
        void* test_ptr_2 = malloc(cols * sizeof(double));
        if (test_ptr_2 == NULL) {
            free(test_ptr_1);
            free(test_ptr_m);
            return NULL;
        }
        temp_matrix->matrix[i] = (double*)test_ptr_2;
    }
    return temp_matrix;
}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE* matrix_file = fopen(path_file, "r");
    if (matrix_file == NULL) {
        return NULL;
    }

    void* test_ptr_m = malloc(sizeof(struct Matrix));
    if (test_ptr_m == NULL) {
        fclose(matrix_file);
        return NULL;
    }
    Matrix* temp_matrix = (Matrix*)test_ptr_m;
    if (fscanf(matrix_file, "%zu %zu", &temp_matrix->rows, &temp_matrix->cols) != 2) {
        fclose(matrix_file);
        free(temp_matrix);
        return NULL;
    }
    void** test_ptr_1 = (void**)malloc(temp_matrix->rows * sizeof(double));
    if (test_ptr_1 == NULL) {
        fclose(matrix_file);
        free(temp_matrix);
        return NULL;
    }
    temp_matrix->matrix = (double**)test_ptr_1;
    for (size_t i = 0; i < temp_matrix->rows; ++i) {
        void* test_ptr_2 = malloc(temp_matrix->cols * sizeof(double));
        if (test_ptr_2 == NULL) {
            fclose(matrix_file);
            free(temp_matrix->matrix);
            free(temp_matrix);
            return NULL;
        }
        temp_matrix->matrix[i] = (double*)test_ptr_2;
        for (size_t j = 0; j <temp_matrix->cols; ++j) {
            if (fscanf(matrix_file, "%lf", &temp_matrix->matrix[i][j]) != 1) {
                free(temp_matrix->matrix);
                free(temp_matrix);
                fclose(matrix_file);
                return NULL;
            }
        }
    }
    if (fclose(matrix_file) != 0) {
        return NULL;
    }
    return temp_matrix;
}

int get_rows(const Matrix* matrix, size_t* rows) {
    *rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    *cols = matrix->cols;
    return 0;
}

int free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->rows; ++i) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    *val = matrix->matrix[row][col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    matrix->matrix[row][col] = val;
    return 0;
}

Matrix* mul_scalar(const Matrix* matrix, double val) {
    Matrix* temp_matrix = create_matrix(matrix->rows, matrix->cols);
    for (size_t i = 0; i < temp_matrix->rows; ++i) {
        for (size_t j = 0; j < temp_matrix->cols; ++j) {
            temp_matrix->matrix[i][j] = matrix->matrix[i][j] * val;
        }
    }
    return temp_matrix;
}

Matrix* transp(const Matrix* matrix) {
    Matrix* temp_matrix = create_matrix(matrix->cols, matrix->rows);
    for (size_t i = 0; i < matrix->cols; ++i) {
        for (size_t j = 0; j < matrix->rows; ++j) {
            temp_matrix->matrix[i][j] = matrix->matrix[j][i];
        }
    }
    return temp_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    Matrix* temp_matrix = create_matrix(l->rows, l->cols);

    for (size_t i = 0; i < l->rows; ++i) {
        for (size_t j = 0; j < l->cols; ++j) {
            temp_matrix->matrix[i][j] = l->matrix[i][j] + r->matrix[i][j];
        }
    }

    return temp_matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    Matrix* temp_matrix = create_matrix(l->rows, l->cols);

    for (size_t i = 0; i < l->rows; ++i) {
        for (size_t j = 0; j < l->cols; ++j) {
            temp_matrix->matrix[i][j] = l->matrix[i][j] - r->matrix[i][j];
        }
    }

    return temp_matrix;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l->cols != r->rows) {
        return NULL;
    }

    Matrix* temp_matrix = create_matrix(l->rows, r->cols);

    for (size_t i = 0; i < l->rows; ++i) {
        for (size_t j = 0; j < r->cols; ++j) {
            temp_matrix->matrix[i][j]= 0;
            for (size_t k = 0; k < l->cols; ++k)
                temp_matrix->matrix[i][j] += l->matrix[i][k] * r->matrix[k][j];
        }
    }

    return temp_matrix;
}

int minus_row_col(double **origin_matrix, double **temp_matrix, size_t row, size_t col, size_t m_size) {
    size_t miss_row = 0;
    for (size_t i = 0; i < m_size - 1; ++i) {
        if (i == row) {
            miss_row = 1;
        }
        size_t miss_col = 0;
        for (size_t j = 0; j < m_size - 1; ++j) {
            if (j == col) {
                miss_col = 1;
            }
            temp_matrix[i][j] = origin_matrix[i + miss_row][j + miss_col];
        }
    }
    return 0;
}

double recursive_det(double **origin_matrix, size_t m_size) {
    double temp_det = 0;
    if (m_size < 1) {
        return 0;
    }
    if (m_size == 1) {
        temp_det = origin_matrix[0][0];
        return(temp_det);
    }
    if (m_size == 2) {
        temp_det = origin_matrix[0][0] * origin_matrix[1][1] - (origin_matrix[1][0] * origin_matrix[0][1]);
        return(temp_det);
    }
    double** temp_matrix = (double**)malloc(sizeof(double*)*m_size);
    if (temp_matrix == NULL) {
        return 0;
    }

    for (size_t i = 0; i < m_size; ++i) {
        temp_matrix[i] = (double*)malloc(sizeof(double) * m_size);
        if (temp_matrix[i] == NULL) {
            free(temp_matrix);
            return 0;
        }
    }
    int sign = 1;
    for (size_t i = 0; i < m_size; ++i) {
        if (minus_row_col(origin_matrix, temp_matrix, i, 0, m_size) != 0) {
            return 0;
        }
        temp_det = temp_det + sign * origin_matrix[i][0] * recursive_det(temp_matrix, m_size - 1);
        sign = -sign;
    }
    for (size_t i = 0; i < m_size; ++i) {
        free(temp_matrix[i]);
    }
    free(temp_matrix);
    return(temp_det);
}

int det(const Matrix* matrix, double* val) {
    *val = recursive_det(matrix->matrix, matrix->rows);
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    Matrix* temp_matrix = create_matrix(matrix->rows, matrix->cols);
    int sign = 1;
    for (size_t i = 0; i < temp_matrix->rows; ++i) {
        for (size_t j = 0; j < temp_matrix->cols; ++j) {
            Matrix* additions_matrix = create_matrix(temp_matrix->rows - 1, temp_matrix->cols - 1);
            if (minus_row_col(matrix->matrix, additions_matrix->matrix, j, i, temp_matrix->rows) != 0) {
                return NULL;
            }
            if ((i + j) % 2 == 0) {
                sign = 1;
            } else {
                sign = -1;
            }
            temp_matrix->matrix[i][j] = sign * recursive_det(additions_matrix->matrix,
                                                             additions_matrix->rows);
            free_matrix(additions_matrix);
        }
    }
    return temp_matrix;
}

Matrix* inv(const Matrix* matrix) {
    if (matrix->cols == 1) {
        Matrix* temp_matrix = create_matrix(1, 1);
        temp_matrix->matrix[0][0] = 1 / matrix->matrix[0][0];
        return temp_matrix;
    }
    Matrix* adj_temp = adj(matrix);
    Matrix* temp_matrix = mul_scalar(adj_temp, (1 / recursive_det(matrix->matrix, matrix->rows)));
    free_matrix(adj_temp);
    return temp_matrix;
}
