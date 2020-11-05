OBJS := main.o Hero.o Monster.o JSON.o
CFLAGS := -Wall -Wextra -std=c++17
CC := g++-9

build: $(OBJS)
	$(CC) $(CFLAGS) -o game $(OBJS)

main.o: main.cpp Hero.h Monster.h JSON.h
	$(CC) $(CFLAGS) -c main.cpp

Hero.o: Hero.cpp Hero.h Monster.h JSON.h
	$(CC) $(CFLAGS) -c Hero.cpp

Monster.o: Monster.cpp Monster.h JSON.h
	$(CC) $(CFLAGS) -c Monster.cpp

jsonparser.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) -c JSON.cpp

static-code-analysis:
	chmod +x cppcheck_test.sh
	./cppcheck_test.sh

memory-leak-check:
	chmod +x memory_test.sh
	./memory_test.sh

run_unit_tests:
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest.a
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
	g++ -std=c++17 -o game *.cpp
	cd test && cmake CMakeLists.txt && make && ./unitTests

io-diff-tests:
	chmod +x run_test.sh
	./run_test.sh game results.txt
	diff test/results.txt test/expected_results.txt

documentation:
	doxygen doxconf

clean:
	rm -rf *.out *.o game ./DOCS
