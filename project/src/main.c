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

    main_pointers* pointers = create_main_pointers();
    if (pointers == NULL) {
        fclose(mail);
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
        if (strcmp(line, "\r\n") == 0 || strcmp(line, "\n\r") == 0 || line[0] == '\n' || line[0] == '\r') {
            break;
        }

        // check for additional information for "From" header

        if (from_fl) {
            if (unique_extra_inf(&pointers->from, &line, mail) != 0) {
                free_pointers(pointers, mail);
                free(line);
                return ALLOC_ERR;
            }
            from_fl = false;
        }

        // check for additional information for "To" header

        if (to_fl) {
            if (unique_extra_inf(&pointers->to, &line, mail) != 0) {
                free_pointers(pointers, mail);
                free(line);
                return ALLOC_ERR;
            }
            to_fl = false;
        }

        // check for additional information for "Date" header

        if (date_fl) {
            if (unique_extra_inf(&pointers->date, &line, mail) != 0) {
                free_pointers(pointers, mail);
                free(line);
                return ALLOC_ERR;
            }
            date_fl = false;
        }

    	int search_result;

        // searching for "From" header

        search_result = find_simple_header(&pointers->from, &line, "From:", &amount);
        if (search_result == SUCCESSFUL_SEARCH) {
            from_fl = true;
        }
        if (search_result == ALLOC_ERR) {
            free_pointers(pointers, mail);
            free(line);
            return ALLOC_ERR;
        }

        // searching for "To" header

        search_result = find_simple_header(&pointers->to, &line, "To:", &amount);
        if (search_result == SUCCESSFUL_SEARCH) {
            to_fl = true;
        }
        if (search_result == ALLOC_ERR) {
            free_pointers(pointers, mail);
            free(line);
            return ALLOC_ERR;
        }

        // searching for "Date" header

        search_result = find_simple_header(&pointers->date, &line, "Date:", &amount);
        if (search_result == SUCCESSFUL_SEARCH) {
            date_fl = true;
        }
        if (search_result == ALLOC_ERR) {
            free_pointers(pointers, mail);
            free(line);
            return ALLOC_ERR;
        }

        // searching for boundary key

        if (!boundary_set) {
            char* temp_line = tolower_w(line);
            if (strstr(temp_line, " boundary=") != NULL ||
                strstr(temp_line, "\tboundary=") != NULL ||
                strstr(temp_line, ";boundary=") != NULL) {
                size_t index = strstr(temp_line, "boundary=") - temp_line + 9;

                int semicolon_mark, space_mark, quotes_mark;
                free(pointers->boundary);
                char* temp_boundary = strdup(line + index);
                char* first_temp_boundary = remove_segue(temp_boundary, &amount);
                char* semicolon_temp = delete_semicolon(first_temp_boundary, &semicolon_mark);
                char* second_temp_boundary = remove_quotes(semicolon_temp, &quotes_mark);
                pointers->boundary = delete_spaces(second_temp_boundary, &space_mark);
                if (pointers->boundary == NULL) {
                    free_pointers(pointers, mail);
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
            if (strstr(line, pointers->boundary) != NULL) {
                size_t boundary_len = strlen(pointers->boundary);
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

    printf("%s|%s|%s|%d", pointers->from, pointers->to, pointers->date, parts);

    free_pointers(pointers, mail);
    free(line);
    return 0;
}
