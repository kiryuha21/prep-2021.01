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
    char* pointer = strstr(*line, header_name);
    if (pointer == NULL) {
        return 0;
    }
    long header_pos = pointer - *line;
    if (header_pos != 0) {
        return 0;
    }
    free(*header);
    if (strcmp(header_name, "From:") == 0) {
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

int find_boundary(char** header, char** line, int* amount) {
    char* temp_line = tolower_w(*line);
    if (temp_line == NULL) {
        return ALLOC_ERR;
    }
    long boundary_pos = strstr(temp_line, "boundary=") - temp_line - 1;
    if (boundary_pos < 0) {
        free(temp_line);
        return 0;
    }
    if (isalpha((*line)[boundary_pos])) {
        free(temp_line);
        return 0;
    }
    size_t index = boundary_pos + 10;
    if (temp_line[boundary_pos + 9] == ' ' && temp_line[boundary_pos + 10] == '=') {
        ++index;
        if (temp_line[boundary_pos + 11] == ' ') {
            ++index;
        }
    }

    free(*header);
    int semicolon_mark, space_mark, quotes_mark;
    char* temp_boundary = strdup(*line + index);
    char* first_temp_boundary = remove_segue(temp_boundary, amount);
    char* semicolon_temp = delete_semicolon(first_temp_boundary, &semicolon_mark);
    char* second_temp_boundary = remove_quotes(semicolon_temp, &quotes_mark);
    *header = delete_spaces(second_temp_boundary, &space_mark);
    if (*header == NULL) {
        return ALLOC_ERR;
    }
    free(temp_boundary);
    if (first_temp_boundary != NULL && semicolon_mark) {
        free(first_temp_boundary);
    }
    if (semicolon_temp != NULL && quotes_mark) {
        free(semicolon_temp);
    }
    if (second_temp_boundary != NULL && space_mark) {
        free(second_temp_boundary);
    }
    free(temp_line);
    return 1;
}
