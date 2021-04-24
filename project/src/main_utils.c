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

int find_simple_header(char** header, char** line, char* header_name, int* amount) {
    char* pointer;
    if ((pointer = strstr(*line, header_name)) != NULL && *line[0] == header_name[0]) {
        free(*header);
        if (strcmp(header_name,"From:") == 0) {
            int fspace_mark;
            char* temp_from = remove_segue(pointer + 5, amount);
            *header = delete_fspaces(temp_from, &fspace_mark);
            if (fspace_mark) {
                free(temp_from);
            }
        } else {
            *header = remove_segue(pointer + strlen(header_name) + 1, amount);
        }
        if (*header == NULL) {
            return ALLOC_ERR;
        }
        return 1;
    }
    return 0;
}