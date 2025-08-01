BIN := main
OBJ1 := bin/main.o
BIN_DIR := bin
SRC_DIR := src

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN)

$(BIN): $(OBJ1) 
	gcc $(OBJ1) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

MAKE_DIRS:
	mkdir $(BIN_DIR) -p

clean:
	rm -r bin