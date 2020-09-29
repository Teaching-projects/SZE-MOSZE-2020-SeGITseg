#!/bin/bash

touch test/results.txt 
> test/results.txt

./a.out unit_1.json unit_2.json >> test/results.txt
./a.out unit_1.json unit_3.json >> test/results.txt
./a.out unit_2.json unit_1.json >> test/results.txt
./a.out unit_2.json unit_3.json >> test/results.txt
./a.out unit_3.json unit_1.json >> test/results.txt
./a.out unit_3.json unit_2.json >> test/results.txt