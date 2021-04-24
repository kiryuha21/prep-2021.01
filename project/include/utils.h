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
bool free_main_pointers(char* from, char* to, char* date, char* boundary, FILE* mail);

#endif  // PROJECT_INCLUDE_UTILS_H_
