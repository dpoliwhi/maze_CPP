CC=g++
LIB=ar rcs
FLAGS=#-Werror -Wall -Wextra #-std=c++20 
LINUX=-lrt -lpthread -lm -D_GNU_SOURCE
OS=$(shell uname -s)
CFLAGS=-fprofile-arcs -ftest-coverage

s:
	$(CC) $(FLAGS) s21_stack.cpp -o s21_stack
	./s21_stack

v:
	$(CC) $(FLAGS) s21_vector.cpp -o s21_vector
	./s21_vector

l:
	$(CC) $(FLAGS) s21_list.cpp -o s21_list
	./s21_list

m:
	$(CC) $(FLAGS) s21_rbtree.cpp -o s21_rbtree
	./s21_rbtree

as:
	$(CC) $(FLAGS) main.cpp -o main
	./main

map:
	$(CC) $(FLAGS) s21_map.cpp -o map
	./map

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
	rm -rf s21_stack s21_vector s21_list s21_rbtree main map
	rm -rf *.gc* *.o *.a *.out *.info test
	rm -rf report/

check:
	cppcheck --enable=all --language=c++ --suppress=missingIncludeSystem *.cpp *.h
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
	make test
	CK_FORK=no leaks --atExit -- ./test
	#valgrind --leak-check=full --leak-resolution=med ./test
	make clean
