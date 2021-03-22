#include <string.h>

#include "utils.h"

size_t custom_strlen(const char* str) {
    return strlen(str);
}

int custom_pow(int base, int power) {
    if (base == 1) {
        return 1;
        } else {
            int result = 1;
            while (power) {
                if (!(power & 1)) {
                    power /= 2;
                    base *= base;
                } else {
                    --power;
                    result *= base;
                }
            }
            return result;
        }
}
