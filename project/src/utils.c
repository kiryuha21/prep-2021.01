#include "utils.h"

char* remove_quotes(char* original) {
    if (original[0] != '"') {
        return original;
    }
    char* temp = malloc(sizeof(char) * (strlen(original)));
    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = 1; i < strlen(original) - 1; ++i) {
        temp[i - 1] = original[i];
    }
    return temp;
}

char* remove_segue(char* original, int* amount) {
    int size;
    if (original[strlen(original) - 2] == '\r') {
        size = 2;
    } else {
        size = 1;
    }
    *amount = size;
    char* temp = malloc(sizeof(char) * (strlen(original)));
    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < strlen(original) - size; ++i) {
        temp[i] = original[i];
    }
    return temp;
}

char* add_inf_check(char* main_info, char* add_info) {
    int amount;
    if (add_info[0] != ' ') {
        return add_info;
    }
    int size = 0;
    if (add_info[1] == ' ') {
        size = 1;
    }
    add_info = remove_segue(add_info, &amount);
    char* temp = (char*)malloc(sizeof(char) * (strlen(main_info) + strlen(add_info) + 1));
    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < strlen(main_info); ++i) {
        temp[i] = main_info[i];
    }
    for (size_t i = size + strlen(main_info);
                i < strlen(main_info) + strlen(add_info) - amount + size + 2;
                ++i) {
        temp[i] = add_info[i - strlen(main_info)];
    }
    free(add_info);
    return temp;
}

char* delete_spaces(char* original) {
    if (strchr(original, ' ') == NULL) {
        return original;
    }
    char* temp = (char*)malloc(sizeof(char) * strlen(original));
    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < strlen(original); ++i) {
        if (original[i] != ' ') {
            temp[i] = original[i];
        }
    }
    return temp;
}

char* delete_semicolon(char* original) {
    if (strchr(original, ';') == NULL) {
        return original;
    }
    char* temp = (char*)malloc(sizeof(char) * strlen(original));
    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = 0; original[i] != ';'; ++i) {
        temp[i] = original[i];
    }
    return temp;
}

char* delete_fspaces(char* original) {
    if (original[0] != ' ') {
        return original;
    }
    char* temp = (char*)malloc(sizeof(char) * strlen(original));
    if (temp == NULL) {
        return NULL;
    }
    size_t pos;
    for (pos = 0; original[pos] == ' ' ; ++pos) { }
    for (size_t i = pos; i < strlen(original); ++i) {
        temp[i - pos] = original[i];
    }
    //free(original);
    return temp;
}

char* tolower_w(char* original) {
    char* temp = (char*)malloc(sizeof(char) * (strlen(original) + 1));
    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < strlen(original); ++i) {
        temp[i] = (char)tolower(original[i]);
    }
    return temp;
}


size_t find_last_index(char* original, char* to_find) {
    char* pointer;
    if ((pointer = strstr(original, to_find)) == NULL) {
        return -1;
    }
    size_t index;
    char* or_pointer = original;
    for (index = 0; or_pointer != pointer; ++index, ++or_pointer) { }
    index += strlen(to_find);
    return index - 1;
}

char* copy_from(char* original, size_t index) {
    char* temp = (char*)malloc(sizeof(char) * (strlen(original) + 1));
    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = index; i < strlen(original); ++i) {
        temp[i - index] = original[i];
    }
    return temp;
}
