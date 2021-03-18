#include "blackrecord.h"

void blackrecord(FILE *record_file,
                 FILE *transaction_file,
                 FILE *blackrecord_file,
                 data client_data, data transfer) {
    while (fscanf(record_file, "%d%20s%20s%30s%15s%lf%lf%lf",
                        &client_data.number,
                        client_data.name,
                        client_data.surname,
                        client_data.address,
                        client_data.tel_number,
                        &client_data.indebtedness,
                        &client_data.credit_limit,
                        &client_data.cash_payments) != -1) {
        while (fscanf(transaction_file, "%d %lf", &transfer.number, &transfer.cash_payments) != -1) {
            if (client_data.number == transfer.number && transfer.cash_payments != 0) {
                client_data.credit_limit += transfer.cash_payments;
            }
        }
        fprintf(blackrecord_file, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                                client_data.number,
                                client_data.name,
                                client_data.surname,
                                client_data.address,
                                client_data.tel_number,
                                client_data.indebtedness,
                                client_data.credit_limit,
                                client_data.cash_payments);
        rewind(transaction_file);
    }
}
