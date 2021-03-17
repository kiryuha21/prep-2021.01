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
    FILE *Ptr, *Ptr_2 , *blackrecord;
    Data client_data = {0}, transfer = {0};
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1:
                Ptr = fopen("record.dat", "r+");
                if (Ptr == NULL) {
                    puts("Not access");
                } else {
                    masterWrite(Ptr, client_data);
                    fclose(Ptr);
                }
                break;
            case 2:
                Ptr = fopen(filename, "r+");
                if (Ptr == NULL) {
                    puts("Not access");
                } else {
                    transactionWrite(Ptr, transfer);
                    fclose(Ptr);
                }
                break;
            case 3:
                Ptr = fopen("record.dat", "r");
                Ptr_2 = fopen(filename, "r");
                blackrecord = fopen("blackrecord.dat", "w");
                if (Ptr == NULL || Ptr_2 == NULL) {
                    puts("exit");
                } else {
                    blackRecord(Ptr, Ptr_2, blackrecord, client_data, transfer);
                    fclose(Ptr);
                    fclose(Ptr_2);
                    fclose(blackrecord);
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

