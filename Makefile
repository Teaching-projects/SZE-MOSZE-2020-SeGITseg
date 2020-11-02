OBJS := main.o unit.o jsonparser.o
CFLAGS := -Wall -Wextra -std=c++17
CC := g++

build: $(OBJS)
	$(CC) $(CFLAGS) -o game $(OBJS)

main.o: main.cpp unit.h jsonparser.h
	$(CC) $(CFLAGS) -c main.cpp

unit.o: unit.cpp unit.h jsonparser.h
	$(CC) $(CFLAGS) -c unit.cpp

jsonparser.o: jsonparser.cpp jsonparser.h
	$(CC) $(CFLAGS) -c jsonparser.cpp

static-code-analysis:
	bash -c "chmod +x cppcheck_test.sh"
	bash -c "./cppcheck_test.sh"

memory-leak-check:
	bash -c "chmod +x memory_test.sh"
	bash -c "./memory_test.sh"

run_unit_tests:
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest.a
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
	cd test && cmake CMakeLists.txt && make && ./unitTests

io-diff-tests:
	bash -c "chmod +x run_test.sh"
	bash -c "./run_test.sh game results.txt"
	bash -c "diff test/results.txt test/expected_results.txt"

documentation:
	doxygen doxconf

clean:
	rm -rf *.o add ./DOCS