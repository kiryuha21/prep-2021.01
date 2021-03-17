#ifndef PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_
#define PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_

#include "utils.h"
#include <string.h>

void write_to_file(const char* file_name, Data* test_data);
void read_from_file(const char* file_name, Data* test_data);
int data_comparison(Data* data_to_file, Data* data_from_file);
int file_open_read_check(const char* file_name);

#endif  // PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_
