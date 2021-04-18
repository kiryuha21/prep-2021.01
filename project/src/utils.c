#include "utils.h"

char* remove_quotes(char* original, int* mark) {
    if (original == NULL) {
        return NULL;
    }

    if (original[0] != '"') {
        *mark = 0;
        return original;
    }
    size_t orig_len = strlen(original);
    char* temp = malloc(sizeof(char) * (orig_len - 1));

    for (size_t i = 0; i < orig_len - 1; ++i) {
        temp[i] = '\0';
    }

    if (temp == NULL) {
        return NULL;
    }
    for (size_t i = 1; i < orig_len - 1; ++i) {
        temp[i - 1] = original[i];
    }
    original = temp;
    *mark = 1;
    return original;
}

char* remove_segue(char* original, int* amount) {
    int size;
    if (original == NULL) {
        return NULL;
    }

    size_t orig_len = strlen(original);
    if (original[orig_len - 2] == '\r') {
        size = 2;
    } else {
        size = 1;
    }
    *amount = size;
    char* temp = malloc(sizeof(char) * (orig_len - size + 1));

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < orig_len - size + 1; ++i) {
        temp[i] = '\0';
    }

    for (size_t i = 0; i < orig_len - size; ++i) {
        temp[i] = original[i];
    }
    original = temp;
    return original;
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
    size_t main_len = strlen(main_info);
    size_t add_len = strlen(add_info);

    char* temp_add_info = remove_segue(add_info, &amount);
    char* temp = (char*)malloc(sizeof(char) * (main_len + add_len - amount + 1));

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < main_len + add_len - amount + 1; ++i) {
        temp[i] = '\0';
    }

    for (size_t i = 0; i < main_len; ++i) {
        temp[i] = main_info[i];
    }
    for (size_t i = size + main_len; i < main_len + add_len - amount + 1; ++i) {
        temp[i] = temp_add_info[i - main_len];
    }
    free(temp_add_info);
    free(main_info);
    main_info = temp;
    return main_info;
}

char* delete_spaces(char* original, int* mark) {
    if (original == NULL) {
        return NULL;
    }

    if (strchr(original, ' ') == NULL) {
        *mark = 0;
        return original;
    }

    size_t orig_len = strlen(original);
    char* temp = (char*)malloc(sizeof(char) * orig_len);

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < orig_len; ++i) {
        temp[i] = '\0';
    }

    for (size_t i = 0; i < orig_len; ++i) {
        if (original[i] != ' ') {
            temp[i] = original[i];
        }
    }
    original = temp;
    *mark = 1;
    return original;
}

char* delete_semicolon(char* original, int* mark) {
    if (original == NULL) {
        return NULL;
    }

    if (strchr(original, ';') == NULL) {
        *mark = 0;
        return original;
    }

    size_t orig_len = strlen(original);
    char* temp = (char*)malloc(sizeof(char) * orig_len);

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < orig_len; ++i) {
        temp[i] = '\0';
    }

    for (size_t i = 0; original[i] != ';'; ++i) {
        temp[i] = original[i];
    }
    original = temp;
    *mark = 1;
    return original;
}

char* delete_fspaces(char* original, int* mark) {
    if (original[0] != ' ') {
        *mark = 0;
        return original;
    }
    size_t orig_len = strlen(original);
    char* temp = (char*)malloc(sizeof(char) * orig_len);

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < orig_len; ++i) {
        temp[i] = '\0';
    }

    size_t pos;
    for (pos = 0; original[pos] == ' ' ; ++pos) { }
    for (size_t i = pos; i < orig_len; ++i) {
        temp[i - pos] = original[i];
    }
    original = temp;
    *mark = 1;
    return original;
}

char* tolower_w(char* original) {
    size_t orig_len = strlen(original);
    char* temp = (char*)malloc(sizeof(char) * (orig_len + 1));

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < orig_len + 1; ++i) {
        temp[i] = '\0';
    }
    for (size_t i = 0; i < orig_len; ++i) {
        temp[i] = (char)tolower(original[i]);
    }
    original = temp;
    return original;
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
    size_t orig_len = strlen(original);
    char* temp = (char*)malloc(sizeof(char) * (orig_len + 1));
    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < orig_len + 1; ++i) {
        temp[i] = '\0';
    }

    for (size_t i = index; i < orig_len; ++i) {
        temp[i - index] = original[i];
    }
    original = temp;
    return original;
}

int free_main_pointers(char* from, char* to, char* date, char* boundary, FILE* mail) {
    if (from != NULL) {
        free(from);
    }
    if (to != NULL) {
        free(to);
    }
    if (date != NULL) {
        free(date);
    }
    if (boundary != NULL) {
        free(boundary);
    }
    if (mail != NULL) {
        fclose(mail);
    }
    return 0;
}
