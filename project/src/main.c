#include <stdlib.h>
#include <stdio.h>

#include "is_prime.h"
#include "utils.h"

#define ERR_ARGS_COUNT -1
#define ERR_WRONG_FLG -2

#define TST_FOO_FIX 1
#define TST_FOO_IMPL 2
#define TST_MOD_IMPL 3

int strtol_check(const char* end) {
	if (*end != '\0') {
		printf("Ошибка ввода\n");
		return 0;
	}
	return 1;
}

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    char *end = NULL;
    int test_case = strtol(argv[1], &end, 0);
    if (!strtol_check(end)) {
    	return ERR_WRONG_FLG;
    }
    const char* data = argv[2];

    switch (test_case) {
        case TST_FOO_FIX: {
            printf("%zu\n", custom_strlen(data));
            break;
        }
        case TST_FOO_IMPL: {
            if (argc != 4) {
                return ERR_ARGS_COUNT;
            }
            int base = strtol(data, &end, 0);
            if (!strtol_check(end)) {
    			return ERR_WRONG_FLG;
    		}
            int pow =  strtol(argv[3], &end, 0);
            if (!strtol_check(end)) {
    			return ERR_WRONG_FLG;
    		}
            printf("%i\n", custom_pow(base, pow));
            break;
        }
        case TST_MOD_IMPL: {
            int num = strtol(data, &end, 0);
            if (!strtol_check(end)) {
    			return ERR_WRONG_FLG;
    		}
            printf("%d\n", is_prime(num));
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }

    return 0;
}
