BIN := main
OBJ := bin/main.o bin/writeToFile.o bin/readFromFile.o bin/createFile.o
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN)

$(BIN): $(OBJ)
	gcc $(OBJ) -o $(PROC_DIR)/$@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

MAKE_DIRS:
	mkdir bin -p
	mkdir proc -p

clean:
	rm -r bin proc