GXX=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
CFLAGS=--coverage
TEST=-lgtest
OS=$(shell uname -s)
LINUX=-lrt -lpthread -lm -D_GNU_SOURCE
DIRBUILD=build/

all: test check clean

install: clean build copy

copy:
	mkdir $(HOME)/Applications/3DViewer/
	cp -rf $(DIRBUILD)3D_Viewer.app $(HOME)/Applications/3DViewer/
	cp -rf $(DIRBUILD)../Objects $(HOME)/Applications/3DViewer/
	cp -rf Readme $(HOME)/Applications/3DViewer/
	mkdir $(HOME)/Applications/3DViewer/Resources/
	cp $(DIRBUILD)../Resources/settings.conf $(HOME)/Applications/3DViewer/Resources/
	mkdir $(HOME)/Applications/3DViewer/Gif/
	mkdir $(HOME)/Applications/3DViewer/Screenshots/
	open $(HOME)/Applications/3DViewer/

build:
	mkdir $(DIRBUILD)
	cp 3D_Viewer.pro $(DIRBUILD)
	cd $(DIRBUILD) && qmake 3D_Viewer.pro && make

uninstall:
	rm -rf $(HOME)/Applications/3DViewer

test:
ifeq ($(OS), Darwin)
	$(GXX) test.cpp  Model/*.cpp Controller/*.cpp -o test $(TEST)
	./test
else
	$(GXX) test.cpp  Model/*.cpp Controller/*.cpp -o test $(TEST) $(LINUX)
	./test
endif

dist:
	tar -cvf 3DViewer.tar .
	open .
dvi:
	open $(HOME)/Applications/3DViewer/Readme/readme.html | open Readme/readme.html

clean:
	rm -rf *.o *.out *.a *.gcda *.gcno *.info *.tar test
	rm -rf $(DIRBUILD)
	rm -rf $(HOME)/Applications/3DViewer/

check: cpplint
	cppcheck --enable=all --suppress=operatorEqVarError --suppress=missingInclude --suppress=unusedFunction --language=c++ --suppress=unusedStructMember Model/*.* Controller/*.* Settings/*.* View/*.cpp View/*.h OpenGL/*.*
	# valgrind --leak-check=full --leak-resolution=med ./test
	CK_FORK=no leaks --atExit -- ./test
	make clean

cpplint:
	cp -f linters/CPPLINT.cfg ./
	python3 linters/cpplint.py --extensions=cpp  Model/*.* Controller/*.* Settings/*.* View/*.cpp View/*.h OpenGL/*.*
	rm -rf CPPLINT.cfg
