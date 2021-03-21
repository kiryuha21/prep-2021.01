#include "input_output_check.h"

bool write_to_file(FILE* file_name, data* test_data) {
    if (fprintf(file_name, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                test_data->number,
                test_data->name,
                test_data->surname,
                test_data->address,
                test_data->tel_number,
                test_data->indebtedness,
                test_data->credit_limit,
                test_data->cash_payments) != -1) {
        return 1;
    } else {
        return 0;
    }
}

bool read_from_file(FILE* file_name, data* test_data) {
    if (fscanf(file_name, "%d%20s%20s%30s%15s%lf%lf%lf",
               &test_data->number,
               test_data->name,
               test_data->surname,
               test_data->address,
               test_data->tel_number,
               &test_data->indebtedness,
               &test_data->credit_limit,
               &test_data->cash_payments) != -1) {
        return 1;
    } else {
        return 0;
    }
}

bool read_to_data(data* test_data) {
    if (scanf("%d%20s%20s%30s%15s%lf%lf%lf",
               &test_data->number,
               test_data->name,
               test_data->surname,
               test_data->address,
               test_data->tel_number,
               &test_data->indebtedness,
               &test_data->credit_limit,
               &test_data->cash_payments) != -1) {
        return 1;
    } else {
        return 0;
    }
}

bool read_to_part_data(data* test_data) {
    if (scanf("%d %lf", &test_data->number, &test_data->cash_payments) != -1) {
        return 1;
    } else {
        return 0;
    }
}

bool read_from_part_file(FILE* file_name, data* test_data) {
    if (fscanf(file_name, "%d %lf", &test_data->number, &test_data->cash_payments) != -1) {
        return 1;
    } else {
        return 0;
    }
}

bool write_to_part_file(FILE* file_name, data* test_data) {
    if (fprintf(file_name, "%-3d%-6.2f\n", test_data->number, test_data->cash_payments) != -1) {
        return 1;
    } else {
        return 0;
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
