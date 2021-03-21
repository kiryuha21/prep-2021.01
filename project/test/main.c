#include "file_open_read_check.h"
#include "blackrecord.h"
#include "masterwrite.h"
#include "transaction.h"
#include "utils.h"

int main() {
    if (file_open_read_check("io_test")) {
        puts("everything is working properly");
    } else {
        puts("input/output error");
    }
    return 0;
}

/* bool file_open_read_check(FILE* file_name) {
    data data_to_file = {1, "name1", "surname1", "address1", "telnum1", 0, 12, 144};
    write_to_file(file_name, &data_to_file);
    data data_from_file;
    read_from_file(file_name, &data_from_file);
    bool compare = data_comparison(&data_to_file, &data_from_file);
    if (!compare) {
        puts("writing or reading error\n");
    }
    return compare;
} */
