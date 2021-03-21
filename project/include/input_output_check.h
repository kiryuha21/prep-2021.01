#ifndef PROJECT_INCLUDE_INPUT_OUTPUT_CHECK_H_
#define PROJECT_INCLUDE_INPUT_OUTPUT_CHECK_H_

#include "utils.h"
#include <string.h>

bool write_to_file(FILE* file_name, data* test_data);
bool read_from_file(FILE* file_name, data* test_data);
bool data_comparison(data* data_to_file, data* data_from_file);
bool part_data_comparison(data* data_to_file, data* data_from_file);
bool read_to_data(data* test_data);
bool read_to_part_data(data* test_data);
bool read_from_part_file(FILE* file_name, data* test_data);
bool write_to_part_file(FILE* file_name, data* test_data);

#endif  // PROJECT_INCLUDE_INPUT_OUTPUT_CHECK_H_
