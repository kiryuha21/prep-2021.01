#include "utils.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];

    char* from, *to, *date, *boundary = (char*)(malloc(sizeof(char) * 1024));

    int parts = 0;
    int add_arr_size = 0;
    FILE* mail = fopen(path_to_eml, "r");

    char** additions_arr = (char**) malloc(sizeof(char*));
    additions_arr[0] = (char*) malloc(sizeof(char)*1024);

    char* line = (char*)(malloc(sizeof(char)*1024));

    // header processing

    while (!feof(mail)) {
        fgets(line, 1024, mail);
        if (strlen(line) == 1) {
            break;
        }

        char* pointer;
        if ((pointer = strstr(line, "From")) != NULL) {
        from = remove_segue(pointer + 6);
        }

        if ((pointer = strstr(line, "To")) != NULL) {
            to = remove_segue(pointer + 4);
        }

        if ((pointer = strstr(line, "Date")) != NULL) {
            date = remove_segue(pointer + 6);
        }

        if ((pointer = strstr(line, "boundary=")) != NULL) {
            boundary = remove_quotes(remove_segue(pointer + 9));
        }

        if (line[0] == ' ') {
            if (add_arr_size != 0) {
                char** test_ptr = (char**) realloc(additions_arr, add_arr_size + sizeof(char*));
                if (test_ptr == NULL) {
                    return ALLOC_ERR;
                } else {
                additions_arr = test_ptr;
                }
                additions_arr[add_arr_size] = malloc(sizeof(char) * 1024);
            }
            additions_arr[add_arr_size] = remove_segue(line);
            ++add_arr_size;
        }
    }

    // body processing

    bool empty_lines = true;
    while (!feof(mail)) {
        fgets(line, 1024, mail);
        if (strlen(line) > 1) {
            empty_lines = false;
        }

        if (strstr(line, boundary) != NULL) {
            ++parts;
        }
    }
    if (empty_lines) {
        parts = 0;
    } else {
        parts -= 2;
    }
    printf("%s|%s|%s|%d", from, to, date, parts);

    free(additions_arr);

    fclose(mail);
    return 0;
}
