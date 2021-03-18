#include "utils.h"
#include "transactionwrite.h"
#include "masterwrite.h"
#include "blackrecord.h"
#include "file_open_read_check.h"

#define IO_OPERATORS_ERR -1;
#define DATA_RECORD 1
#define TRANSACTION_DATA_RECORD 2
#define BLACKRECORD_OPERATION 3

void choice_print() {
    puts("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
}

int main(void) {
    if (file_open_read_check("file_for_io_test") == 0) {
        return IO_OPERATORS_ERR;
    }
    int choice = 0;
    FILE *record_file, *transaction_file , *blackrecord_file;
    data client_data = {0}, transfer = {0};
    choice_print();
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case DATA_RECORD:
                record_file = fopen("record.dat", "r+");
                if (record_file == NULL) {
                    puts("Not access");
                } else {
                    master_write(record_file, client_data);
                    fclose(record_file);
                }
                break;
            case TRANSACTION_DATA_RECORD:
                transaction_file = fopen(filename, "r+");
                if (transaction_file == NULL) {
                    puts("Not access");
                } else {
                    transaction_write(transaction_file, transfer);
                    fclose(transaction_file);
                }
                break;
            case 3:
                record_file = fopen("record.dat", "r");
                transaction_file = fopen(filename, "r");
                blackrecord_file = fopen("blackrecord.dat", "w");
                if (record_file == NULL || transaction_file == NULL || blackrecord_file == NULL) {
                    puts("exit");
                } else {
                    blackrecord(record_file, transaction_file, blackrecord_file, client_data, transfer);
                    fclose(record_file);
                    fclose(transaction_file);
                    fclose(blackrecord_file);
                }
                break;
            default:
                puts("error");
                break;
        }
        choice_print();
    }
    return 0;
}

