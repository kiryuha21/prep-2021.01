#include "blackrecord.h"

bool blackrecord(FILE *record_file,
                 FILE *transaction_file,
                 FILE *blackrecord_file,
                 data client_data, data transfer) {
    while (read_from_file(record_file, &client_data)) {
        while (read_from_part_file(transaction_file, &transfer)) {
            if (client_data.number == transfer.number && transfer.cash_payments != 0) {
                client_data.credit_limit += transfer.cash_payments;
            }
        }
        if (!write_to_file(blackrecord_file, &client_data)) {
            return 0;
        }
        rewind(transaction_file);
    }
    return 1;
}
