all:
	mkdir -p bin
	gcc src/add.c -g -c -o bin/add.o
	gcc src/delete.c -g -c -o bin/delete.o
	gcc src/get.c -g -c -o bin/get.o
	gcc src/getAll.c -g -c -o bin/getAll.o
	gcc src/search.c -g -c -o bin/search.o
	gcc src/freeList.c -g -c -o bin/freeList.o
	gcc src/main.c -g -c -o bin/main.o
	gcc bin/*.o -o main