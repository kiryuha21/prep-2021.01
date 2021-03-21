#include "masterwrite.h"

void master_write_print() {
    puts("1 Number account: \n2 Client name: \n3 Surname: \n4 Address client: ");
    puts("5 Client Telnum: \n6 Client indebtedness: \n7 Client credit limit: \n8 Client cash payments: \n\n");
}

bool master_write(FILE *record_file, data Client)  {
    master_write_print();
    while (read_to_data(&Client)) {
        if (!write_to_file(record_file, &Client)) {
            return 0;
        }
        master_write_print();
    }
    return 1;
}
