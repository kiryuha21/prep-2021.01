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