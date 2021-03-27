#include "matrix.h"


int main(void) {
	Matrix* a = create_matrix_from_file("matrix_ex.dat");
	double element;
	get_elem(a, 0, 0, &element);
	set_elem(a, 0, 0, element);
	size_t value;
	get_cols(a, &value);
	get_rows(a, &value);
	det(a, &element);
	Matrix* b = transp(a);
	Matrix* c = sum(a, b);
	free_matrix(c);
	c = sub(a, b);
	free_matrix(c);
	c = mul(a, b);
	free_matrix(c);
	c = inv(a);
	free_matrix(c);
	free_matrix(b);
	free_matrix(a);
    return 0;
}

