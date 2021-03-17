#include "transactionwrite.h"

void transactionWrite(FILE* ofPTR, Data transfer) {
    printf("%s\n%s\n",
           "1 Number account: ",
           "2 Client cash payments: ");
    while (scanf("%d %lf", &transfer.Number, &transfer.cash_payments) != -1) {
        fprintf(ofPTR, "%-3d%-6.2f\n", transfer.Number, transfer.cash_payments);
        printf("%s\n%s\n",
               "1 Number account:",
               "2 Client cash payments: ");
    }
}
