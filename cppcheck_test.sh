#!/bin/bash

IFS=$'\n'

echo "$(cppcheck *.cpp --enable=warning --output-file=cppcheck_log.txt)"

if [ ! -s ./cppcheck_log.txt ]; then
    echo "The test did not find any warnings/errors."
    echo "$(cppcheck *.cpp --enable=performance,style --output-file=performance_log.txt)"

    if [ ! -s ./performance_log.txt ]; then
        echo "The test did not find any performance/style errors."
    else
        echo "Performance/style errors found."
    fi
else
    echo "The test found some errors!"
    exit 1
fi
