#include "file_open_read_check.h"

void write_to_file(const char* file_name, data* test_data) {
    FILE* ptr = fopen(file_name, "w");
    if (ptr == NULL) {
        puts("Not access");
    } else {
        fprintf(ptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                test_data->number,
                test_data->name,
                test_data->surname,
                test_data->address,
                test_data->tel_number,
                test_data->indebtedness,
                test_data->credit_limit,
                test_data->cash_payments);
        fclose(ptr);
    }
}

void read_from_file(const char* file_name, data* test_data) {
    FILE* ptr = fopen(file_name, "r");
    if (ptr == NULL) {
        puts("Not access");
    } else {
        fscanf(ptr, "%d%20s%20s%30s%15s%lf%lf%lf",
               &test_data->number,
               test_data->name,
               test_data->surname,
               test_data->address,
               test_data->tel_number,
               &test_data->indebtedness,
               &test_data->credit_limit,
               &test_data->cash_payments);
        fclose(ptr);
    }
}

bool data_comparison(data* data_to_file, data* data_from_file) {
    return  strcmp(data_to_file->name, data_from_file->name) == 0 &&
            data_to_file->number == data_from_file->number &&
            strcmp(data_to_file->surname, data_from_file->surname) == 0 &&
            strcmp(data_to_file->address, data_from_file->address) == 0 &&
            strcmp(data_to_file->tel_number, data_from_file->tel_number) == 0 &&
            data_to_file->indebtedness == data_from_file->indebtedness &&
            data_to_file->credit_limit == data_from_file->credit_limit &&
            data_to_file->cash_payments == data_from_file->cash_payments;
}

bool file_open_read_check(const char* file_name) {
    data data_to_file = {1, "name1", "surname1", "address1", "telnum1", 0, 12, 144};
    write_to_file(file_name, &data_to_file);
    data data_from_file;
    read_from_file(file_name, &data_from_file);
    bool compare = data_comparison(&data_to_file, &data_from_file);
    if (!compare) {
        puts("writing or reading error\n");
    }
    return compare;
}
