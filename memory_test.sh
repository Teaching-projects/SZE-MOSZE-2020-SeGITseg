#!/bin/bash

IFS=$'\n'
command="$(valgrind --leak-check=yes --log-file=memorytest_log.txt ./a.out run_test.sh)"

result="$(cat ./memorytest_log.txt)"

echo $result

if [ "$(echo $result | sed 's/^.*ERROR SUMMARY: \([0-9]*\) errors.*$/\1/')" == "0" ]; then
    echo "The test did not find any memory leaks."
else
    echo "The test found memory leaks!"
    exit 1
fi
