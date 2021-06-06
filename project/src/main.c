#include "utils.h"
#include "transactionwrite.h"
#include "masterwrite.h"
#include "blackrecord.h"

#define FILE_ACCESS_ERR  -1
#define FCLOSE_ERR       -2

#define DATA_RECORD             1
#define TRANSACTION_DATA_RECORD 2
#define BLACKRECORD_OPERATION   3

void choice_print() {
    puts("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
}

int main(void) {
    int choice = 0;
    FILE *record_file, *transaction_file , *blackrecord_file;
    data client_data = {0}, transfer = {0};
    choice_print();
    while (scanf("%d", &choice) > 0) {
        switch (choice) {
            case DATA_RECORD:
                record_file = fopen("record.dat", "r+");
                if (record_file == NULL) {
                    puts("Not access");
                    return FILE_ACCESS_ERR;
                } else {
                    if (!master_write(record_file, client_data)) {
                        puts("master_write error");
                    }
                    if (fclose(record_file) != 0) {
                        puts("fclose error");
                        return FCLOSE_ERR;
                    }
                }
                break;
            case TRANSACTION_DATA_RECORD:
                transaction_file = fopen(filename, "r+");
                if (transaction_file == NULL) {
                    puts("Not access");
                    return FILE_ACCESS_ERR;
                } else {
                    if (!transaction_write(transaction_file, transfer)) {
                        puts("transaction_write error");
                    }
                    if (fclose(transaction_file) != 0) {
                        puts("fclose error");
                        return FCLOSE_ERR;
                    }
                }
                break;
            case 3:
                record_file = fopen("record.dat", "r");
                transaction_file = fopen(filename, "r");
                blackrecord_file = fopen("blackrecord.dat", "w");
                if (record_file == NULL || transaction_file == NULL || blackrecord_file == NULL) {
                    if (record_file != NULL) {
                        fclose(record_file);
                    }
                    if (transaction_file != NULL) {
                        fclose(transaction_file);
                    }
                    if (blackrecord_file != NULL) {
                        fclose(blackrecord_file);
                    }
                    puts("Not access");
                    return FILE_ACCESS_ERR;
                } else {
                    if (!blackrecord(record_file,
                                     transaction_file,
                                     blackrecord_file,
                                     client_data,
                                     transfer)) {
                        puts("blackrecord error");
                    }
                    if (fclose(record_file) != 0 ||
                        fclose(transaction_file) != 0 ||
                        fclose(blackrecord_file) != 0) {
                        puts("fclose error");
                        return FCLOSE_ERR;
                    }
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
