#!/usr/bin/env bash

PROG_PATH=${1}  # ./test_main.out
ROOT=$(dirname $(realpath $0))

IN="1
1
name1
surname1
address1
telnum1
0
12
144"

echo "${IN}" | eval "${PROG_PATH}"

IN="2
1
144"