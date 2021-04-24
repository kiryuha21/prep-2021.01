#ifndef PROJECT_INCLUDE_MAIN_UTILS_H_
#define PROJECT_INCLUDE_MAIN_UTILS_H_

#include "utils.h"

int unique_extra_inf(char** header, char** line, FILE* mail);

int find_simple_header(char** header, char** line, char* header_name, int* amount);

int find_boundary(char** header, char** line, int* amount);

#endif  // PROJECT_INCLUDE_MAIN_UTILS_H_
