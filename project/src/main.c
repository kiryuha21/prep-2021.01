#include "utils.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];

    FILE* mail = fopen(path_to_eml, "r");
    if (mail == NULL) {
        return OPEN_ERR;
    }

    char *from, *to, *date, *boundary;

    int parts = 0, amount;

    char* line = (char*)(malloc(sizeof(char)*2400000));
    if (line == NULL) {
        return ALLOC_ERR;
    }

    bool from_fl = false, to_fl = false, date_fl = false, boundary_set = false;

    // header processing

    while (!feof(mail)) {
        fgets(line, 2400000, mail);
        if (strcmp(line, "\r\n") == 0 || line[0] == '\n') {
            break;
        }

        if (from_fl) {
            while (true) {
                char* temp_from = add_inf_check(from, line);
                if (temp_from == line) {
                    break;
                } else {
                    from = temp_from;
                    fgets(line, 2400000, mail);
                }
            }
            from_fl = false;
        }

        if (to_fl) {
            while (true) {
                char* temp_to = add_inf_check(to, line);
                if (temp_to == line) {
                    break;
                } else {
                    to = temp_to;
                    fgets(line, 2400000, mail);
                }
            }
            to_fl = false;
        }

        if (date_fl) {
            while (true) {
                char* temp_date = add_inf_check(date, line);
                if (temp_date == line) {
                    break;
                } else {
                    date = temp_date;
                    fgets(line, 2400000, mail);
                }
            }
            date_fl = false;
        }

        char *pointer;
        if ((pointer = strstr(line, "From:")) != NULL && line[0] == 'F') {
            from = delete_fspaces(remove_segue(pointer + 5, &amount));
            if (from == NULL) {
                if (to != NULL) {
                    free(to);
                }
                free(line);
                if (date != NULL) {
                    free(date);
                }
                if (boundary != NULL) {
                    free(boundary);
                }
                return ALLOC_ERR;
            }
            from_fl = true;
        }

        if ((pointer = strstr(line, "To:")) != NULL && line[0] == 'T') {
            to = remove_segue(pointer + 4, &amount);
            if (to == NULL) {
                if (from != NULL) {
                    free(from);
                }
                free(line);
                if (date != NULL) {
                    free(date);
                }
                if (boundary != NULL) {
                    free(boundary);
                }
                return ALLOC_ERR;
            }
            to_fl = true;
        }

        if ((pointer = strstr(line, "Date:")) != NULL && line[0] == 'D') {
            date = remove_segue(pointer + 6, &amount);
            if (date == NULL) {
                if (to != NULL) {
                    free(to);
                }
                free(line);
                if (from != NULL) {
                    free(from);
                }
                if (boundary != NULL) {
                    free(boundary);
                }
                return ALLOC_ERR;
            }
            date_fl = true;
        }

        if (!boundary_set) {
            char* temp_line = tolower_w(line);
            if (strstr(temp_line, " boundary=") != NULL ||
                strstr(temp_line, "\tboundary=") != NULL ||
                strstr(temp_line, ";boundary=") != NULL) {

                size_t index = find_last_index(temp_line, "boundary=");
                char* temp_boundary = copy_from(line, index + 1);
                char* to_shorten_line = delete_semicolon(remove_segue(temp_boundary, &amount));
                boundary = delete_spaces(remove_quotes(to_shorten_line));
                if (boundary == NULL) {
                    if (to != NULL) {
                        free(to);
                    }
                    free(line);
                    if (from != NULL) {
                        free(from);
                    }
                    if (date != NULL) {
                        free(date);
                    }
                    return ALLOC_ERR;
                }
                boundary_set = true;
            }
        }
    }

    // body processing

    bool empty_lines = true;
    while (!feof(mail)) {
        fgets(line, 2400000, mail);
        if (strlen(line) > 1) {
            empty_lines = false;
        }

        if (boundary_set) {
            if (strstr(line, boundary) != NULL &&
                strcmp(boundary, "") != 0) {
                if ((amount == 2 && strlen(boundary) == strlen(line) - 4) ||
                    (amount == 1 && strlen(boundary) == strlen(line) - 3))
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
    if (to == NULL) {
        to = (char*)malloc(sizeof(char));
    }
    if (from == NULL) {
        from = (char*)malloc(sizeof(char));
    }
    if (date == NULL) {
        date = (char*)malloc(sizeof(char));
    }

    printf("%s|%s|%s|%d", from, to, date, parts);

    fclose(mail);
    free(to);
    free(line);
    free(date);
    free(from);
    if (boundary_set) {
        free(boundary);
    }
    return 0;
}