CC=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
TEST=-lgtest
CFLAGS=--coverage
DIRBUILD=build/

all: clean test

install: build copy

copy:
	mkdir $(HOME)/Applications/dpoliwhi_calc/
	cp -rf $(DIRBUILD)s21_calculator.app $(HOME)/Applications/dpoliwhi_calc/
	open $(HOME)/Applications/dpoliwhi_calc/

build:
	mkdir $(DIRBUILD)
	cp s21_calc_cpp/View/s21_calculator.pro $(DIRBUILD)
	cd $(DIRBUILD) && qmake s21_calculator.pro && make

dvi:
	open Readme.md

dist:
	tar -cvf s21_calc_tar.tar s21_calc_cpp/* readme.html Makefile

dist_open:
	open s21_calc_tar.tar

test:
	$(CC) $(FLAGS) $(CFLAGS) test.cpp s21_calc_cpp/Model/s21_model.cpp s21_calc_cpp/Controller/s21_controller.cpp -o test $(TEST)
	./test

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	make open_report

open_report:
	open report/index.html


clean:
	rm -rf *.out *.o *.a *.gcda *.gcno *.info test
	rm -rf $(DIRBUILD)
	rm -rf $(HOME)/Applications/dpoliwhi_calc/
	rm -rf s21_calc_tar.tar s21_calc_tar
	rm -rf report

check: test
	cppcheck --enable=all --suppress=unknownMacro --suppress=missingInclude --suppress=unusedFunction s21_calc_cpp/*/*.cpp *.h
	python3 ../materials/linters/cpplint.py --extensions=cpp s21_calc_cpp/*/*.cpp *.h
	CK_FORK=no leaks --atExit -- ./test
	make clean
