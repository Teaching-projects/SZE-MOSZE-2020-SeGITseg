OBJS := main.o unit.o jsonparser.o
CFLAGS := -Wall -std=c++17
CC := g++

build: $(OBJS)
	$(CC) $(CFLAGS) -o add $(OBJS)

main.o: main.cpp unit.h jsonparser.h
	$(CC) $(CFLAGS) -c main.cpp

unit.o: unit.cpp unit.h jsonparser.h
	$(CC) $(CFLAGS) -c unit.cpp

jsonparser.o: jsonparser.cpp jsonparser.h
	$(CC) $(CFLAGS) -c jsonparser.cpp

run_unit_tests:
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest.a
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
	cd test && cmake CMakeLists.txt && make && ./unitTests