#include "is_prime.h"

int is_prime(int value) {
    if (value == 2) {
		return 1;
	} else if (value % 2 == 0 || value < 2) {
		return 0;
	}

	for (int i = 3; i * i < value; i+=2) {
		if (value % i == 0) return 0;
	}

	return 1;
}
