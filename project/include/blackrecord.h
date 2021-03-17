#ifndef PROJECT_INCLUDE_BLACKRECORD_H_
#define PROJECT_INCLUDE_BLACKRECORD_H_

#include "utils.h"

void blackRecord(FILE *ofPTR,
                 FILE  *ofPTR_2,
                 FILE *blackrecord,
                 struct masterRecord client_data,
                 struct masterRecord transfer);

#endif  // PROJECT_INCLUDE_BLACKRECORD_H_
