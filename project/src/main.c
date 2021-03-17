#include "utils.h"
#include "transactionwrite.h"
#include "masterwrite.h"
#include "blackrecord.h"

int main(void) {
    int choice = 0;
    FILE *Ptr, *Ptr_2 , *blackrecord;
    Data client_data = {0}, transfer = {0};
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1:
                Ptr = fopen("/home/kiryuha21/prep-2021.01/btests/record.dat", "r+");
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
                Ptr = fopen("/home/kiryuha21/prep-2021.01/btests/record.dat", "r");
                Ptr_2 = fopen(filename, "r");
                blackrecord = fopen("/home/kiryuha21/prep-2021.01/btests/blackrecord.dat", "w");
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

