all:
	gcc src/convert.c -c -o bin/convert.o
	gcc src/task1.c -c -o bin/task1.o
	gcc src/task2.c -c -o bin/task2.o
	gcc src/task3.c -c -o bin/task3.o
	gcc src/task4.c -c -o bin/task4.o
	gcc src/main.c -c -o bin/main.o
	gcc bin/main.o bin/convert.o bin/task1.o bin/task2.o bin/task3.o bin/task4.o -o main