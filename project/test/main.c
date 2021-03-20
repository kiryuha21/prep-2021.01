#include "file_open_read_check.h"
#include "blackrecord.h"
#include "masterwrite.h"
#include "transaction.h"
#include "utils.h"

int main() {
    if (file_open_read_check("io_test")) {
        puts("everything is working properly");
    } else {
        puts("input/output error");
    }
    return 0;
}