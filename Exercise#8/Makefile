all:
	mkdir -p bin
	mkdir -p bin/lib
	mkdir -p bin/calc
	gcc src/calc/add.c -c -fPIC -o bin/calc/add.o
	gcc src/calc/divi.c -c -fPIC -o bin/calc/divi.o
	gcc src/calc/mult.c -c -fPIC -o bin/calc/mult.o
	gcc src/calc/sub.c -c -fPIC -o bin/calc/sub.o

	gcc --shared bin/calc/*.o -o bin/lib/libcalc.so 

	gcc src/main.c -c -o bin/main.o
	gcc src/printMenu.c -c -o bin/printMenu.o
	gcc src/getTwoNumber.c -c -o bin/getTwoNumber.o

	gcc bin/main.o bin/printMenu.o bin/getTwoNumber.o -L./bin/lib -lcalc -o main
PWD:=$(shell pwd)/bin/lib
start:
	LD_LIBRARY_PATH=$(PWD) ./main