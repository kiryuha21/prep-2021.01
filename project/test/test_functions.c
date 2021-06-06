#include "test_functions.h"

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

int file_read_write_compare(FILE** test_file, data* data_to_file, data* data_from_file) {
    if (!open_file(test_file, "io_tests", "w")) {
        return FILE_OPEN_ERR;
    }

    if (write_to_file(*test_file, data_to_file)) {
        puts("\nwrite_to_file stage passed");
    } else {
        puts("\nwrite_to_file stage error");
        return WRITING_ERR;
    }

    if (!close_file(test_file)) {
        return FILE_CLOSE_ERR;
    }
    if (!open_file(test_file, "io_tests", "r")) {
        return FILE_OPEN_ERR;
    }

    if (read_from_file(*test_file, data_from_file)) {
        puts("read_from_file stage passed");
    } else {
        puts("read_from_file stage error");
        return READING_ERR;
    }

    if (data_comparison(data_from_file, data_to_file)) {
        puts("first data_comparison stage passed");
    } else {
        puts("first data_comparison stage error");
    }

    if (!close_file(test_file)) {
        return FILE_CLOSE_ERR;
    }

    return 1;
}

int part_file_read_write_compare(FILE** test_file, data* data_to_file, data* data_from_file) {
    if (!open_file(test_file, "io_tests", "w")) {
        return FILE_OPEN_ERR;
    }

    if (write_to_part_file(*test_file, data_to_file)) {
        puts("write_to_part_file stage passed");
    } else {
        puts("write_to_part_file stage failed");
        return WRITING_ERR;
    }

    if (!close_file(test_file)) {
        return FILE_CLOSE_ERR;
    }
    if (!open_file(test_file, "io_tests", "r")) {
        return FILE_OPEN_ERR;
    }

    if (read_from_part_file(*test_file, data_to_file)) {
        puts("write_to_part_file stage passed");
    } else {
        puts("write_to_part_file stage failed");
        return WRITING_ERR;
    }

    if (part_data_comparison(data_from_file, data_to_file)) {
        puts("first part_data_comparison stage passed");
    } else {
        puts("first part_data_comparison stage error");
        return COMPARISON_ERR;
    }

    if (!close_file(test_file)) {
        return FILE_CLOSE_ERR;
    }

    return 1;
}

int struct_read_compare(data* data_from_file, data *data_to_file) {
    if (read_to_struct(data_from_file)) {
        puts("read_to_struct stage success");
    } else {
        puts("read_to_struct stage error");
    return READING_ERR;
    }

    if (data_comparison(data_from_file, data_to_file)) {
        puts("second data_comparison stage passed");
    } else {
        puts("second data_comparison stage error");
    }

    return 1;
}

int part_struct_read_compare(data* data_from_file, data* data_to_file) {
    if (read_to_part_struct(data_from_file)) {
        puts("read_to_part_struct stage success");
    } else {
        puts("read_to_part_struct stage error");
        return READING_ERR;
    }

    if (part_data_comparison(data_from_file, data_to_file)) {
        puts("second part_data_comparison stage passed");
    } else {
        puts("second part_data_comparison stage error");
        return COMPARISON_ERR;
    }

    return 1;
}