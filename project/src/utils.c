#include "utils.h"

char* remove_quotes(char* original) {
    if (original[0] != '"') {
        return original;
    }
    char* temp = malloc(sizeof(char) * (strlen(original) - 2));
    for (size_t i = 1; i < strlen(original) - 1; ++i) {
        temp[i - 1] = original[i];
    }
    return temp;
}

char* remove_segue(char* original) {
    char* temp = malloc(sizeof(char) * (strlen(original)));
    for (size_t i = 0; i < strlen(original) - 1; ++i) {
        temp[i] = original[i];
    }
    return temp;
}
