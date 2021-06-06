#!/usr/bin/env bash

PROG_PATH=${1}  # ./main.out
ROOT=$(dirname $(realpath $0))

RECORDS_F_NAME="record.dat"
TRANSACTIONS_F_NAME="transaction.dat"
BLACKRECORDS_F_NAME="blackrecord.dat"

rm -f $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME
touch $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME

IN="1
3
name_3
surname_3
address_3
tel_3
1000
200
420
4
name_4
surname_4
address_4
tel_4
2000
1337
144"

echo "${IN}" | eval "${PROG_PATH}"

IN="2
4
228
3
12"

echo "${IN}" | eval "${PROG_PATH}"

IN="3"

echo "${IN}" | eval "${PROG_PATH}"

for file in $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME; do
	diff -uN $file $ROOT/${file}.gold
	if [[ "$?" != "0" ]]; then
		echo "Files mismatches"
		exit 1
	fi
done