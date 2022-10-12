.PHONY: all install uninstall clean dvi dist tests gcov_report lint leaks

CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
FOLDER=../build/
INNER_FOLDER=$(FOLDER)s21_calculator/

ifeq ($(OS), Linux)
  LIBS=-lcheck -lpthread -lrt -lm -lsubunit
else
  LIBS=-lcheck
endif

all: dvi

build: clean
	mkdir $(FOLDER)
	mkdir $(INNER_FOLDER)
	cp *.c *.h  $(FOLDER)
	cd s21_calculator; cp *.h *.cpp *.ui *.pro *.icns ../$(FOLDER)s21_calculator
	cd $(INNER_FOLDER); qmake s21_calculator.pro
	make -C $(INNER_FOLDER)
	cd $(FOLDER); rm -rf *.c *.h
	cd $(INNER_FOLDER); rm -rf *.c *.h *.cpp *.ui *.o *.ts *.pro *.qrc Makefile

install: build
	cp -rf $(INNER_FOLDER)s21_calculator.app $(HOME)/Desktop/
	make clean

uninstall: 
	rm -rf $(HOME)/Desktop/s21_calculator.app

dist:
	rm -rf smart_calc_sjoannie_arch
	mkdir smart_calc_sjoannie_arch
	mkdir smart_calc_sjoannie_arch/s21_calculator
	mkdir smart_calc_sjoannie_arch/html
	cp Makefile *.c *.h smart_calc_sjoannie_arch/
	cd html; cp *.html *.png ../smart_calc_sjoannie_arch/html
	cd ./s21_calculator; cp *.cpp *.h *.pro *.ui *.icns ../smart_calc_sjoannie_arch/s21_calculator
	tar -cvzf $(HOME)/Desktop/smart_calc_sjoannie_arch.tgz smart_calc_sjoannie_arch/

tests:
	$(CC) $(CFLAGS) -c s21_smart_calc.c -o s21_smart_calc.o
	ar rcs s21_smart_calc.a s21_smart_calc.o
	ranlib s21_smart_calc.a
	$(CC) $(CFLAGS) s21_test.c s21_smart_calc.a $(LIBS) -o s21_calculator.out
	./s21_calculator.out

cppcheck:
	cppcheck --suppress=missingIncludeSystem *.c *.h

lint:
	cp lint/CPPLINT.cfg .
	python3 lint/cpplint.py --extensions=c *.c
	rm -f CPPLINT.cfg

gcov_report: tests
	$(CC) --coverage s21_test.c s21_smart_calc.c -o test $(LIBS)
	./test
	lcov -t "test" -c -d . -o test.info
	genhtml test.info -o report
	open -a "Google Chrome" report/index.html

leaks: tests
	CK_FORK=no leaks --atExit -- ./s21_calculator.out

clean: 
	rm -f *.o *.a *.gcno *.gcda *.info *.out 
	rm -rf ./report
	rm -rf ../build
	rm -rf $(HOME)/Desktop/smart_calc_sjoannie_arch.tar.gz
	rm -rf smart_calc_sjoannie_arch
