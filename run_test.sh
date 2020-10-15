#!/bin/bash

touch test/results.txt 
> test/results.txt

./a.out units/unit_1.json units/unit_2.json >> test/results.txt
./a.out units/unit_1.json units/unit_3.json >> test/results.txt
./a.out units/unit_2.json units/unit_1.json >> test/results.txt
./a.out units/unit_2.json units/unit_3.json >> test/results.txt
./a.out units/unit_3.json units/unit_1.json >> test/results.txt
./a.out units/unit_3.json units/unit_2.json >> test/results.txt