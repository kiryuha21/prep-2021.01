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
    char* temp = calloc(orig_len - 1, sizeof(char));

    if (temp == NULL) {
        return NULL;
    }

    memcpy(temp, original + 1, orig_len - 2);

    *mark = 1;
    return temp;
}

char* remove_segue(char* original, int* amount) {
    int size;
    if (original == NULL) {
        return NULL;
    }

    size_t orig_len = strlen(original);
    if (original[orig_len - 2] == '\r' || original[orig_len - 2] == '\n') {
        size = 2;
    } else {
        size = 1;
    }
    *amount = size;
    char* temp = calloc((orig_len - size + 1), sizeof(char));

    if (temp == NULL) {
        return NULL;
    }

    memcpy(temp, original, orig_len - size);

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
    size_t main_len = strlen(main_info);
    size_t add_len = strlen(add_info);

    char* temp_add_info = remove_segue(add_info, &amount);
    char* temp = (char*)calloc((main_len + add_len - amount + 1), sizeof(char));

    if (temp == NULL || temp_add_info == NULL) {
        return NULL;
    }

    strcpy(temp, main_info);
    memcpy(temp + main_len, temp_add_info + size, add_len - amount);

    free(temp_add_info);
    free(main_info);
    return temp;
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
    char* temp = (char*)calloc(orig_len, sizeof(char));

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < orig_len; ++i) {
        if (original[i] != ' ') {
            temp[i] = original[i];
        }
    }
    *mark = 1;
    return temp;
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
    char* temp = (char*)calloc(orig_len, sizeof(char));

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; original[i] != ';'; ++i) {
        temp[i] = original[i];
    }

    *mark = 1;
    return temp;
}

char* delete_fspaces(char* original, int* mark) {
    if (original[0] != ' ') {
        *mark = 0;
        return original;
    }
    size_t orig_len = strlen(original);
    char* temp = (char*)calloc(orig_len, sizeof(char));

    if (temp == NULL) {
        return NULL;
    }

    size_t pos;
    for (pos = 0; original[pos] == ' ' ; ++pos) { }
    memcpy(temp, original + pos, orig_len - pos);

    *mark = 1;
    return temp;
}

char* tolower_w(char* original) {
    size_t orig_len = strlen(original);
    char* temp = (char*)calloc((orig_len + 1), sizeof(char));

    if (temp == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < orig_len; ++i) {
        temp[i] = (char)tolower(original[i]);
    }

    return temp;
}

bool free_main_pointers(main_pointers* pointers) {
    if (pointers != NULL) {
        if (pointers->from != NULL) {
            free(pointers->from);
        }
        if (pointers->to != NULL) {
            free(pointers->to);
        }
        if (pointers->date != NULL) {
            free(pointers->date);
        }
        if (pointers->boundary != NULL) {
            free(pointers->boundary);
        }
        free(pointers);
    }
    return true;
}

bool free_pointers(main_pointers* pointers, FILE* mail) {
    free_main_pointers(pointers);
    if (mail != NULL) {
        fclose(mail);
    }
    return true;
}

main_pointers* create_main_pointers() {
    main_pointers* temp_pointers = (main_pointers*) calloc(1, sizeof(main_pointers));
    if (temp_pointers == NULL) {
        return NULL;
    }
    temp_pointers->from = (char*)calloc(1, sizeof(char));
    temp_pointers->to = (char*)calloc(1, sizeof(char));
    temp_pointers->date = (char*)calloc(1, sizeof(char));
    temp_pointers->boundary = (char*)calloc(1, sizeof(char));
    if (temp_pointers->from == NULL || temp_pointers->to == NULL || temp_pointers->date == NULL || temp_pointers->boundary == NULL) {
        free_main_pointers(temp_pointers);
        return NULL;
    }
    return temp_pointers;
}
