#include "file_open_read_check.h"

void write_to_file(const char* file_name, Data* test_data) {
    FILE* ptr;
    ptr = fopen(file_name, "w");
    if (ptr == NULL) {
        puts("Not access");
    } else {
        fprintf(ptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                test_data->Number,
                test_data->Name,
                test_data->Surname,
                test_data->address,
                test_data->TelNumber,
                test_data->indebtedness,
                test_data->credit_limit,
                test_data->cash_payments);
        fclose(ptr);
    }
}

void read_from_file(const char* file_name, Data* test_data) {
    FILE* ptr;
    ptr = fopen(file_name, "r");
    if (ptr == NULL) {
        puts("Not access");
    } else {
        fscanf(ptr, "%d%20s%20s%30s%15s%lf%lf%lf",
               &test_data->Number,
               test_data->Name,
               test_data->Surname,
               test_data->address,
               test_data->TelNumber,
               &test_data->indebtedness,
               &test_data->credit_limit,
               &test_data->cash_payments);
        fclose(ptr);
    }
}

int data_comparison(Data* data_to_file, Data* data_from_file) {
    if (strcmp(data_to_file->Name, data_from_file->Name) == 0 &&
        data_to_file->Number == data_from_file->Number &&
        strcmp(data_to_file->Surname, data_from_file->Surname) == 0 &&
        strcmp(data_to_file->address, data_from_file->address) == 0 &&
        strcmp(data_to_file->TelNumber, data_from_file->TelNumber) == 0 &&
        data_to_file->indebtedness == data_from_file->indebtedness &&
        data_to_file->credit_limit == data_from_file->credit_limit &&
        data_to_file->cash_payments == data_from_file->cash_payments) {
            return 1;
    } else {
        return 0;
    }
}

int file_open_read_check(const char* file_name) {
    Data data_to_file = {1, "name1", "surname1", "address1", "telnum1", 0, 12, 144};
    write_to_file(file_name, &data_to_file);
    Data data_from_file;
    read_from_file(file_name, &data_from_file);
    if (data_comparison(&data_to_file, &data_from_file) == 0) {
        printf("writing or reading error\n");
        return 0;
    }
    FILE* ptr;
    ptr = fopen(file_name, "w");
    if (ptr == NULL) {
        puts("Not access");
        return 0;
    } else {
        fclose(ptr);
    }
    return 1;
}
