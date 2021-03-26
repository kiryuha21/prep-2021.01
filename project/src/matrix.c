#include "matrix.h"

Matrix* create_matrix(size_t rows, size_t cols) {
    void* test_ptr_m = malloc(sizeof(struct Matrix));
    if (test_ptr_m == NULL) {
        return NULL;
    }
    Matrix* temp_matrix = (Matrix*)test_ptr_m;
    temp_matrix->rows = rows;
    temp_matrix->cols = cols;
    void** test_ptr_1 = (void**)malloc(rows * sizeof(double));
    if (test_ptr_1 == NULL) {
        return NULL;
    }
    temp_matrix->matrix = (double**)test_ptr_1;
    for (size_t i = 0;i < rows;++i) {
        void* test_ptr_2 = malloc(cols * sizeof(double));
        if (test_ptr_2 == NULL) {
            return NULL;
        }
        temp_matrix->matrix[i] = (double*)test_ptr_2;
    }
    return temp_matrix;
}

int get_rows(const Matrix* matrix, size_t* rows) {
    (*rows) = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    (*cols) = matrix->cols;
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

Matrix* create_matrix_from_file(const char* path_file) {
    FILE* matrix_file;
    void* test_ptr_m = malloc(sizeof(struct Matrix));
    if (test_ptr_m == NULL) {
        return NULL;
    }
    Matrix* temp_matrix = (Matrix*)test_ptr_m;
    matrix_file = fopen(path_file, "r");
    if (matrix_file == NULL) {
        return NULL;
    }
    if (fscanf(matrix_file, "%lu %lu", &temp_matrix->rows, &temp_matrix->cols) != 2) {
        return NULL;
    }
    void** test_ptr_1 = (void**)malloc(temp_matrix->rows * sizeof(double));
    if (test_ptr_1 == NULL) {
        return NULL;
    }
    temp_matrix->matrix = (double**)test_ptr_1;
    for (size_t i = 0;i < temp_matrix->rows;++i) {
        void* test_ptr_2 = malloc(temp_matrix->cols * sizeof(double));
        if (test_ptr_2 == NULL) {
            return NULL;
        }
        temp_matrix->matrix[i] = (double*)test_ptr_2;
        for (size_t j = 0;j <temp_matrix->cols;++j) {
            if (fscanf(matrix_file, "%lf", &temp_matrix->matrix[i][j]) != 1) {
                return NULL;
            }
        }
    }
    if (fclose(matrix_file) != 0) {
        return NULL;
    }
    return temp_matrix;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    (*val) = matrix->matrix[row][col];
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

int det(const Matrix* matrix, double* val) {
	if (matrix->cols != matrix->rows) {
		return DET_ERR;
	}

	Matrix* temp_matrix = create_matrix(matrix->rows, matrix->cols);
	for (size_t i = 0; i < matrix->rows; ++i) {
		for (size_t j = 0; j < matrix->cols; ++j) {
			temp_matrix->matrix[i][j] = matrix->matrix[i][j];
		}
	}

	double tmp;
    for (size_t k = 0; k < matrix->cols - 1; k++) {
        for (size_t i = k + 1; i < matrix->cols; i++) {
            tmp = -temp_matrix->matrix[i][k] / temp_matrix->matrix[k][k];
            for (size_t j = 0; j < matrix->cols; j++) {
                temp_matrix->matrix[i][j] += temp_matrix->matrix[k][j] * tmp;
            }
        }
    }
    double temp_det = 1;
    for (size_t i = 0; i < matrix->cols; i++) {
        temp_det *= temp_matrix->matrix[i][i];
    }
    *val = temp_det;
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    Matrix* temp_matrix = create_matrix(matrix->rows, matrix->cols);
    return temp_matrix;
}

Matrix* inv(const Matrix* matrix) {
    Matrix* temp_matrix = create_matrix(matrix->rows, matrix->cols);
    return temp_matrix;
}
