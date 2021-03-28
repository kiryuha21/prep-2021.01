#include "matrix.h"


int main(void) {
	Matrix* first_test_matrix = create_matrix_from_file("matrix_ex.dat");
    if (first_test_matrix == NULL) {
        return CREATE_ERR;
    }

	double element = 0;
	if (get_elem(first_test_matrix, 0, 0, &element) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        return GET_ERR;
    }

	if (set_elem(first_test_matrix, 0, 0, element) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        return SET_ERR;
    }

	size_t value = 0;
	if (get_cols(first_test_matrix, &value) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        return GET_ERR;
    }

	if (get_rows(first_test_matrix, &value) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        return GET_ERR;
    }

	if (det(first_test_matrix, &element) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        return DET_ERR;
    }

	Matrix* second_test_matrix = transp(first_test_matrix);
    if (second_test_matrix == NULL) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        return TRANSP_ERR;
    }

	Matrix* third_test_matrix = sum(first_test_matrix, second_test_matrix);
    if (third_test_matrix == NULL) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        if (free_matrix(second_test_matrix) != 0) {
            return FREE_ERR;
        }
        return SUM_ERR;
    }

	if (free_matrix(third_test_matrix) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        if (free_matrix(second_test_matrix) != 0) {
            return FREE_ERR;
        }
        return FREE_ERR;
    }

	third_test_matrix = sub(first_test_matrix, second_test_matrix);
    if (third_test_matrix == NULL) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        if (free_matrix(second_test_matrix) != 0) {
            return FREE_ERR;
        }
        return SUB_ERR;
    }

	if (free_matrix(third_test_matrix) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        if (free_matrix(second_test_matrix) != 0) {
            return FREE_ERR;
        }
        return FREE_ERR;
    }

	third_test_matrix = mul(first_test_matrix, second_test_matrix);
    if (third_test_matrix == NULL) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        if (free_matrix(second_test_matrix) != 0) {
            return FREE_ERR;
        }
        return MUL_ERR;
    }

	if (free_matrix(third_test_matrix) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        if (free_matrix(second_test_matrix) != 0) {
            return FREE_ERR;
        }
        return FREE_ERR;
    }

	third_test_matrix = inv(first_test_matrix);
    if (third_test_matrix == NULL) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        if (free_matrix(second_test_matrix) != 0) {
            return FREE_ERR;
        }
        return INV_ERR;
    }

	if (free_matrix(third_test_matrix) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        if (free_matrix(second_test_matrix) != 0) {
            return FREE_ERR;
        }
        return FREE_ERR;
    }

	if (free_matrix(second_test_matrix) != 0) {
        if (free_matrix(first_test_matrix) != 0) {
            return FREE_ERR;
        }
        return FREE_ERR;
    }

	if (free_matrix(first_test_matrix) != 0) {
        return FREE_ERR;
    }
    return 0;
}

