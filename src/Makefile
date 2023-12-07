all: install open

install: clean
	mkdir build
	cd build/ && qmake6 ../CPP_calculator.pro && make

open:
	cd build/CPP_calculator.app/Contents/MacOS/ && ./CPP_calculator

uninstall:
	rm -rf build

dvi:
	doxygen doxygen/doxyconfig
	open html/index.html

dist:
	tar -cf archive.tar *.h *.pro *.cc *.ui CPP_calculator.pro.user

tests:
	g++ -std=c++17 tests.cc parser.cc -lgtest -o test
	-./test
	rm -rf *.o test

gcov_report:
	g++ -c -std=c++17 parser.cc --coverage
	g++ -c -std=c++17 tests.cc
	g++ -std=c++17 parser.o tests.o -lgtest -lgcov -o test
	-./test
	lcov -o tests.info -c -d .
	genhtml -o report tests.info
	open ./report/index.html

clean:
	rm -rf *.o test report *.gcno *.gcda *.gcov *.info build html latex *.tar

style:
	clang-format -n -style=google *.cc *.h
	clang-format -i -style=google *.cc *.h