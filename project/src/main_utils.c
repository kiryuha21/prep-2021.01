#include "main_utils.h"

int unique_extra_inf(char** header, char** line, FILE* mail) {
    size_t line_size = 0;
    while (true) {
        char* temp = add_inf_check(*header, *line);
        if (temp == NULL) {
            return ALLOC_ERR;
        }
        if (temp == *line) {
            break;
        } else {
            *header = temp;
            getline(line, &line_size, mail);
        }
    }
    return 0;
}

int find_from_header(char** header, char** line, int* amount) {
    char* pointer;
    if ((pointer = strstr(*line, "From:")) != NULL && *line[0] == 'F') {
        int fspace_mark;
        free(header);
        char* temp_from = remove_segue(pointer + 5, amount);
        *header = delete_fspaces(temp_from, &fspace_mark);
        if (*header == NULL) {
            return ALLOC_ERR;
        }
        if (fspace_mark) {
            free(temp_from);
        }
        return 1;
    }
    return 0;
}