#include "transactionwrite.h"

void transaction_print() {
    puts("1 Number account: \n2 Client cash payments: \n");
}

bool transaction_write(FILE* transaction_file, data transfer) {
    transaction_print();
    while (scanf("%d %lf", &transfer.number, &transfer.cash_payments) != -1) {
        if (fprintf(transaction_file, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments) == -1) {
            return 0;
        }
        transaction_print();
    }
    return 1;
}
