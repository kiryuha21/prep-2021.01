#include "transactionwrite.h"

void transaction_print() {
    puts("1 Number account: \n2 Client cash payments: \n");
}

bool transaction_write(FILE* transaction_file, data transfer) {
    transaction_print();
    while (read_to_part_data(&transfer)) {
        if (!write_to_part_file(transaction_file, &transfer)) {
            return 0;
        }
        transaction_print();
    }
    return 1;
}
