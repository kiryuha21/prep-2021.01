#include "input_output_check.h"

#define FILE_OPEN_ERR   -1
#define FILE_CLOSE_ERR  -2
#define READING_ERR     -3
#define WRITING_ERR     -4
#define COMPARISON_ERR  -5

bool open_file(FILE** test_file, const char* file_name, const char* mode) {
    *test_file = fopen(file_name, mode);
    if (*test_file == NULL) {
        puts("no access");
        return 0;
    } else {
        return 1;
    }
}

bool close_file(FILE** test_file) {
    if (fclose(*test_file) != 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    FILE* test_file;
    if (!open_file(&test_file, "io_tests", "w")) {
        return FILE_OPEN_ERR;
    }

    data data_to_file = {1, "name1", "surname1", "address1", "telnum1", 0, 12, 144};
    if (write_to_file(test_file, &data_to_file)) {
        puts("\nwrite_to_file stage passed");
    } else {
        puts("\nwrite_to_file stage error");
        return WRITING_ERR;
    }

    if (!close_file(&test_file)) {
        return FILE_CLOSE_ERR;
    }
    if (!open_file(&test_file, "io_tests", "r")) {
        return FILE_OPEN_ERR;
    }

    data data_from_file;
    if (read_from_file(test_file, &data_from_file)) {
        puts("read_from_file stage passed");
    } else {
        puts("read_from_file stage error");
        return READING_ERR;
    }

    if (data_comparison(&data_from_file, &data_to_file)) {
        puts("first data_comparison stage passed\n");
    } else {
        puts("first data_comparison stage error\n");
    }

    if (!close_file(&test_file)) {
        return FILE_CLOSE_ERR;
    }
    if (!open_file(&test_file, "io_tests", "w")) {
        return FILE_OPEN_ERR;
    }

    if (write_to_part_file(test_file, &data_to_file)) {
        puts("write_to_part_file stage passed");
    } else {
        puts("write_to_part_file stage failed");
        return WRITING_ERR;
    }

    if (!close_file(&test_file)) {
        return FILE_CLOSE_ERR;
    }
    if (!open_file(&test_file, "io_tests", "r")) {
        return FILE_OPEN_ERR;
    }

    if (read_from_part_file(test_file, &data_to_file)) {
        puts("write_to_part_file stage passed");
    } else {
        puts("write_to_part_file stage failed");
        return WRITING_ERR;
    }

    if (part_data_comparison(&data_from_file, &data_to_file)) {
        puts("first part_data_comparison stage passed\n");
    } else {
        puts("first part_data_comparison stage error\n");
        return COMPARISON_ERR;
    }

    if (!close_file(&test_file)) {
        return FILE_CLOSE_ERR;
    }

    if (read_to_data(&data_from_file)) {
        puts("read_to_data stage success");
    } else {
        puts("read_to_data stage error");
        return READING_ERR;
    }

    if (data_comparison(&data_from_file, &data_to_file)) {
        puts("second data_comparison stage passed\n");
    } else {
        puts("second data_comparison stage error\n");
    }

    if (read_to_part_data(&data_from_file)) {
        puts("read_to_part_data stage success");
    } else {
        puts("read_to_part_data stage error");
        return READING_ERR;
    }

    if (part_data_comparison(&data_from_file, &data_to_file)) {
        puts("second part_data_comparison stage passed\n\n");
    } else {
        puts("second part_data_comparison stage error\n\n");
        return COMPARISON_ERR;
    }

    puts("All tests completed successfully!\n\n");

    return 0;
}
