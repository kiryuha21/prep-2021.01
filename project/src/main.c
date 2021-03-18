#include "utils.h"
#include "transactionwrite.h"
#include "masterwrite.h"
#include "blackrecord.h"
#include "file_open_read_check.h"

int main(void) {
    if (file_open_read_check("file_for_io_test") == 0) {
        return -1;
    }
    int choice = 0;
    FILE *record_file, *transaction_file , *blackrecord_file;
    Data client_data = {0}, transfer = {0};
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1:
                record_file = fopen("record.dat", "r+");
                if (record_file == NULL) {
                    puts("Not access");
                } else {
                    masterWrite(record_file, client_data);
                    fclose(record_file);
                }
                break;
            case 2:
                transaction_file = fopen(filename, "r+");
                if (transaction_file == NULL) {
                    puts("Not access");
                } else {
                    transactionWrite(transaction_file, transfer);
                    fclose(transaction_file);
                }
                break;
            case 3:
                record_file = fopen("record.dat", "r");
                transaction_file = fopen(filename, "r");
                blackrecord_file = fopen("blackrecord.dat", "w");
                if (record_file == NULL || transaction_file == NULL) {
                    puts("exit");
                } else {
                    blackRecord(record_file, transaction_file, blackrecord_file, client_data, transfer);
                    fclose(record_file);
                    fclose(transaction_file);
                    fclose(blackrecord_file);
                }
                break;
            default:
                puts("error");
                break;
        }
        printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    }
    return 0;
}

