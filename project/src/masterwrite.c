#include "masterwrite.h"

void master_write_print() {
    puts("1 Number account: \n2 Client name: \n3 Surname: \n4 Address client: ");
    puts("5 Client Telnum: \n6 Client indebtedness: \n7 Client credit limit: \n8 Client cash payments: \n\n");
}

bool master_write(FILE *record_file, data Client)  {
    master_write_print();
    while (scanf("%d%20s%20s%30s%15s%lf%lf%lf",
                &Client.number,
                Client.name,
                Client.surname,
                Client.address,
                Client.tel_number,
                &Client.indebtedness,
                &Client.credit_limit,
                &Client.cash_payments) != -1) {
        if (fprintf(record_file, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                        Client.number,
                        Client.name,
                        Client.surname,
                        Client.address,
                        Client.tel_number,
                        Client.indebtedness,
                        Client.credit_limit,
                        Client.cash_payments) == -1) {
            return 0;
        }
        master_write_print();
    }
    return 1;
}
