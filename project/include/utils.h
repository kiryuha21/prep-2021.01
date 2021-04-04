#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define OPEN_ERR  (-2)

char* remove_quotes(char* original);
char* remove_segue(char* original, int* amount);
char* add_inf_check(char* main_info, char* add_info);
char* delete_spaces(char* original);
char* delete_semicolon(char* original);

#endif  // PROJECT_INCLUDE_UTILS_H_
