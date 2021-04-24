#include "main_utils.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char* path_to_eml = argv[1];

    FILE* mail = fopen(path_to_eml, "r");
    if (mail == NULL) {
        return OPEN_ERR;
    }

    char* from = (char*)calloc(1, sizeof(char));
    char* to = (char*)calloc(1, sizeof(char));
    char* boundary = (char*)calloc(1, sizeof(char));
    char* date = (char*)calloc(1, sizeof(char));

    if (from == NULL || to == NULL || boundary == NULL || date == NULL) {
    	free_main_pointers(from, to, date, boundary, mail);
        return ALLOC_ERR;
    }

    int parts = 0, amount;

    char* line = NULL;
    size_t line_size = 0;

    bool from_fl = false, to_fl = false, date_fl = false;
    bool boundary_set = false;

    // header processing

    while (!feof(mail)) {
        getline(&line, &line_size, mail);
        if (strcmp(line, "\r\n") == 0 || line[0] == '\n') {
            break;
        }

        // check for additional information for "From" header

        if (from_fl) {
            if (unique_extra_inf(&from, &line, mail) != 0) {
                free_main_pointers(from, to, date, boundary, mail);
                free(line);
                return ALLOC_ERR;
            }
            from_fl = false;
        }

        // check for additional information for "To" header

        if (to_fl) {
            if (unique_extra_inf(&to, &line, mail) != 0) {
                free_main_pointers(from, to, date, boundary, mail);
                free(line);
                return ALLOC_ERR;
            }
            to_fl = false;
        }

        // check for additional information for "Date" header

        if (date_fl) {
            if (unique_extra_inf(&date, &line, mail) != 0) {
                free_main_pointers(from, to, date, boundary, mail);
                free(line);
                return ALLOC_ERR;
            }
            date_fl = false;
        }

        // searching for "From" header

        char* pointer;
        if ((pointer = strstr(line, "From:")) != NULL && line[0] == 'F') {
            int fspace_mark;
            free(from);
            char* temp_from = remove_segue(pointer + 5, &amount);
            from = delete_fspaces(temp_from, &fspace_mark);
            if (from == NULL) {
                free_main_pointers(from, to, date, boundary, mail);
                free(line);
                return ALLOC_ERR;
            }
            if (fspace_mark) {
                free(temp_from);
            }
            from_fl = true;
        }

        // searching for "To" header

        if ((pointer = strstr(line, "To:")) != NULL && line[0] == 'T') {
            free(to);
            to = remove_segue(pointer + 4, &amount);
            if (to == NULL) {
                free_main_pointers(from, to, date, boundary, mail);
                free(line);
                return ALLOC_ERR;
            }
            to_fl = true;
        }

        // searching for "Date" header

        if ((pointer = strstr(line, "Date:")) != NULL && line[0] == 'D') {
            free(date);
            date = remove_segue(pointer + 6, &amount);
            if (date == NULL) {
                free_main_pointers(from, to, date, boundary, mail);
                free(line);
                return ALLOC_ERR;
            }
            date_fl = true;
        }

        // searching for boundary key

        if (!boundary_set) {
            char* temp_line = tolower_w(line);
            if (strstr(temp_line, " boundary=") != NULL ||
                strstr(temp_line, "\tboundary=") != NULL ||
                strstr(temp_line, ";boundary=") != NULL) {
                size_t index = strstr(temp_line, "boundary=") - temp_line + 9;

                int semicolon_mark, space_mark, quotes_mark;
                free(boundary);
                char* temp_boundary = strdup(line + index);
                char* first_temp_boundary = remove_segue(temp_boundary, &amount);
                char* semicolon_temp = delete_semicolon(first_temp_boundary, &semicolon_mark);
                char* second_temp_boundary = remove_quotes(semicolon_temp, &quotes_mark);
                boundary = delete_spaces(second_temp_boundary, &space_mark);
                if (boundary == NULL) {
                    free_main_pointers(from, to, date, boundary, mail);
                    free(line);
                    return ALLOC_ERR;
                }
                if (temp_boundary != NULL) {
                    free(temp_boundary);
                }
                if (first_temp_boundary != NULL && semicolon_mark) {
                    free(first_temp_boundary);
                }
                if (semicolon_temp != NULL && quotes_mark) {
                    free(semicolon_temp);
                }
                if (second_temp_boundary != NULL && space_mark) {
                    free(second_temp_boundary);
                }
                boundary_set = true;
            }
            if (temp_line != NULL) {
                free(temp_line);
            }
        }
    }

    // body processing

    bool empty_lines = true;
    while (!feof(mail)) {
        getline(&line, &line_size, mail);
        size_t line_len = strlen(line);
        if (line_len > 1) {
            empty_lines = false;
            if (!boundary_set) {
                break;
            }
        }

        // searching for matches with boundary key

        if (boundary_set) {
            if (strstr(line, boundary) != NULL) {
                size_t boundary_len = strlen(boundary);
                if ((amount == 2 && boundary_len == line_len - 4) ||
                    (amount == 1 && boundary_len == line_len - 3))
                    ++parts;
            }
        }
    }

    if (empty_lines) {
        parts = 0;
    } else {
        if (!boundary_set) {
            parts = 1;
        }
    }

    printf("%s|%s|%s|%d", from, to, date, parts);

    free_main_pointers(from, to, date, boundary, mail);
    free(line);
    return 0;
}
