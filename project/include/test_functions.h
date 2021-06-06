#ifndef PROJECT_INCLUDE_TEST_FUNCTIONS_H_
#define PROJECT_INCLUDE_TEST_FUNCTIONS_H_

#define FILE_OPEN_ERR   -1
#define FILE_CLOSE_ERR  -2
#define READING_ERR     -3
#define WRITING_ERR     -4
#define COMPARISON_ERR  -5

#include "file_input_output.h"

bool open_file(FILE** test_file, const char* file_name, const char* mode);
bool close_file(FILE** test_file);
int file_read_write_compare(FILE** test_file, data* data_to_file, data* data_from_file);
int part_file_read_write_compare(FILE** test_file, data* data_to_file, data* data_from_file);
int struct_read_compare(data* data_from_file, data *data_to_file);
int part_struct_read_compare(data* data_from_file, data* data_to_file);

#endif  //  PROJECT_INCLUDE_TEST_FUNCTIONS_H_
