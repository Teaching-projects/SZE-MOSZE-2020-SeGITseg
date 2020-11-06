#!/bin/bash

touch test/results1.txt 
> test/results1.txt

touch test/results2.txt 
> test/results2.txt

./game scenario1.json >> test/results1.txt
./game scenario2.json >> test/results2.txt
