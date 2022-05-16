CC=g++
LIB=ar rcs
FLAGS=-Werror -Wall -Wextra
LINUX=-lrt -lpthread -lm -D_GNU_SOURCE
OS=$(shell uname -s)
CFLAGS=-fprofile-arcs -ftest-coverage

all: clean test

test:
ifeq ($(OS), Darwin)
	$(CC) tests/all_tests.cpp -o test -lgtest
	./test
else
	$(CC) tests/all_tests.cpp -o test -lgtest -pthread
	./test
endif

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) tests/all_tests.cpp -o test -lgtest
else
	$(CC) $(CFLAGS) tests/all_tests.cpp -o test -lgtest -pthread
endif
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

clean:
	rm -rf *.gc* *.o *.a *.out *.info test
	rm -rf report/

check:
	cppcheck --enable=all --language=c++ --suppress=missingIncludeSystem --suppress=noExplicitConstructor --suppress=useStlAlgorithm *.cpp *.h
	make test
	CK_FORK=no leaks --atExit -- ./test
	# valgrind --leak-check=full --leak-resolution=med ./test
	make clean
