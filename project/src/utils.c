#include "utils.h"

// removes quotes from "...", returns char* without quotes(unchanged if no quotes)

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

// removes all types of segue: \r \r\n \n\r \n from given char* and return it(unchanged if no segue)

char* remove_segue(char* original, int* amount) {
    if (original == NULL) {
        return NULL;
    }

    size_t orig_len = strlen(original);
    if (orig_len < 3) {
        return NULL;
    }

    int size;
    if (original[orig_len - 2] == '\r' || original[orig_len - 2] == '\n') {
        size = 2;
    } else {
        if (original[orig_len - 1] != '\r' && original[orig_len - 1] != '\n') {
            return original;
        } else {
            size = 1;
        }
    }
    *amount = size;
    char* temp = calloc((orig_len - size + 1), sizeof(char));

    if (temp == NULL) {
        return NULL;
    }

    memcpy(temp, original, orig_len - size);

    return temp;
}

// checks if add_info is an additional information for main_info header,
// if it is any - returns concatenated char*, if there's not - returns add_info

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
    if (temp_add_info == NULL) {
        return NULL;
    }
    char* temp = (char*)calloc((main_len + add_len - amount + 1), sizeof(char));
    if (temp == NULL) {
        return NULL;
    }

    memcpy(temp, main_info, main_len);
    memcpy(temp + main_len, temp_add_info + size, add_len - amount);

    free(add_info);
    free(temp_add_info);
    main_info = temp;
    return main_info;
}

// deletes all spaces from the given char*, returns char*

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

// deletes semicolon from given char*(returns unchanged if there's no semicolon)

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

// deletes all spaces before the first word in given char*(returns unchanged in case of no first spaces)

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

// frees the "main_pointers" struct

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

// frees "main pointers" struct and closes mail file

bool free_pointers(main_pointers* pointers, FILE* mail) {
    free_main_pointers(pointers);
    if (mail != NULL) {
        fclose(mail);
    }
    return true;
}

// creates "main pointers" struct

main_pointers* create_main_pointers() {
    main_pointers* temp_pointers = (main_pointers*) calloc(1, sizeof(main_pointers));
    if (temp_pointers == NULL) {
        return NULL;
    }
    temp_pointers->from = (char*)calloc(1, sizeof(char));
    temp_pointers->to = (char*)calloc(1, sizeof(char));
    temp_pointers->date = (char*)calloc(1, sizeof(char));
    temp_pointers->boundary = (char*)calloc(1, sizeof(char));
    if (temp_pointers->from == NULL || temp_pointers->to == NULL ||
    temp_pointers->date == NULL || temp_pointers->boundary == NULL) {
        free_main_pointers(temp_pointers);
        return NULL;
    }
    return temp_pointers;
}
