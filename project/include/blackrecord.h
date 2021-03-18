#ifndef PROJECT_INCLUDE_BLACKRECORD_H_
#define PROJECT_INCLUDE_BLACKRECORD_H_

#include "utils.h"

void blackRecord(FILE *record_file,
                 FILE *transaction_file,
                 FILE *blackrecord_file,
                 Data client_data, Data transfer);

#endif  // PROJECT_INCLUDE_BLACKRECORD_H_
