#include "test_functions.h"

int main() {
    int error;
    FILE* test_file;
    data data_to_file = {1, "name1", "surname1", "address1", "telnum1", 0, 12, 144};
    data data_from_file;

    error = file_read_write_compare(&test_file, &data_to_file, &data_from_file);
    if (error) {
        puts("\nfirst stage passed\n");
    } else {
        puts("\nfirst stage failed\n");
        return error;
    }

    error = part_file_read_write_compare(&test_file, &data_to_file, &data_from_file);
    if (error) {
        puts("\nsecond stage passed\n");
    } else {
        puts("\nsecond stage failed\n");
        return error;
    }

    error = struct_read_compare(&data_to_file, &data_from_file);
    if (error) {
        puts("\nthird stage passed\n");
    } else {
        puts("\nthird stage failed\n");
        return error;
    }

    error = part_struct_read_compare(&data_from_file, &data_to_file);
    if (error) {
        puts("\nfourth stage passed\n");
    } else {
        puts("\nfourth stage failed\n");
        return error;
    }

    puts("All tests completed successfully!\n\n");

    return 0;
}
