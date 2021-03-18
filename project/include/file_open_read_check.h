#ifndef PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_
#define PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_

#include "utils.h"
#include <string.h>
#include <stdbool.h>

void write_to_file(const char* file_name, data* test_data);
void read_from_file(const char* file_name, data* test_data);
bool data_comparison(data* data_to_file, data* data_from_file);
bool file_open_read_check(const char* file_name);

#endif  // PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_
