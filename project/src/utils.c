#include <string.h>

#include "utils.h"

size_t custom_strlen(const char* str) {
    return strlen(str);
}

int custom_pow(int base, int power) {
    if (base == 1 || power == 0) {
        return 1;
        } else {
            int start = base;
            for (int i = 0; i < power / 2 - 1; ++i) {
                base *= start;
            }

            if (power % 2 == 0) {
                base *= base;
            } else {
                base *= (base * start);
            }
            return base;
        }
}
