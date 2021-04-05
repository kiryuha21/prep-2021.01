#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ALLOC_ERR (-1)
#define OPEN_ERR  (-2)

char* remove_quotes(char* original, int* mark);
char* remove_segue(char* original, int* amount);
char* add_inf_check(char* main_info, char* add_info);
char* delete_spaces(char* original, int* mark);
char* delete_fspaces(char* original, int * mark);
char* delete_semicolon(char* original, int* mark);
char* tolower_w(char* original);
size_t find_last_index(char* original, char* to_find);
char* copy_from(char* original, size_t index);

#endif  // PROJECT_INCLUDE_UTILS_H_
