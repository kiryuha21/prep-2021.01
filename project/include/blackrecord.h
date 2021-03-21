#ifndef PROJECT_INCLUDE_BLACKRECORD_H_
#define PROJECT_INCLUDE_BLACKRECORD_H_

#include "input_output_check.h"

bool blackrecord(FILE *record_file,
                 FILE *transaction_file,
                 FILE *blackrecord_file,
                 data client_data, data transfer);

#endif  // PROJECT_INCLUDE_BLACKRECORD_H_
