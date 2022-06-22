GXX=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
TEST=-lgtest
OS=$(shell uname -s)
LINUX=-lrt -lpthread -lm -D_GNU_SOURCE
DIRBUILD=build/
CHECKDIR=PaintWidget/*.* Controller/*.* View/*.cpp View/*.h Model/*.* Model/Cave/*.* Model/Maze/*.*

all: test check clean

install: clean build copy

build:
	mkdir $(DIRBUILD)
	cd $(DIRBUILD) && qmake ../Maze.pro && make

copy:
	mkdir $(HOME)/Applications/Maze/
	cp -rf $(DIRBUILD)Maze.app $(HOME)/Applications/Maze/
	cp -rf $(DIRBUILD)../Caves $(HOME)/Applications/Maze/
	cp -rf $(DIRBUILD)../Labyrinth $(HOME)/Applications/Maze/
	open $(HOME)/Applications/Maze/

uninstall:
	rm -rf $(HOME)/Applications/Maze
	rm -rf $(DIRBUILD)

dvi:
	open Readme/readme.html

dist:
	tar -cvf Maze.tar .
	open .

test:
ifeq ($(OS), Darwin)
	$(GXX) test.cpp  Model/*.cpp Model/*/*.cpp Controller/*.cpp -o test $(TEST)
	./test
else
	$(GXX)  test.cpp  Model/*.cpp Model/*/*.cpp Controller/*.cpp -o test $(TEST) $(LINUX)
	./test
endif

clean:
	rm -rf *.o *.out *.a *.gcda *.gcno *.info *.tar test
	rm -rf $(DIRBUILD)
	rm -rf $(HOME)/Applications/Maze/

check: cpplint
	cppcheck --enable=all --suppress=missingInclude --suppress=unusedFunction --language=c++ --suppress=unusedStructMember PaintWidget/*.* Controller/*.* Settings/*.* View/*.cpp View/*.h Model/*.* Model/Cave/*.* Model/Maze/*.*
	CK_FORK=no leaks --atExit -- ./test

cpplint:
	cp -f ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=cpp  $(CHECKDIR)
	rm -rf CPPLINT.cfg
