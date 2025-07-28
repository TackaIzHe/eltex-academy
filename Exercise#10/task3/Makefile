BIN := main
OBJ1 := bin/main.o bin/menu.o bin/proc.o
OBJ2 := bin/execProc.o
OBJ3 := bin/split.o
BIN_DIR := bin
SRC_DIR := src

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN)

$(BIN): $(OBJ1) $(OBJ2) $(OBJ3) 
	gcc $(OBJ1) $(OBJ2) $(OBJ3) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/exec/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/splitFunc/%.c 
	gcc $^ -c -o $@


MAKE_DIRS:
	mkdir $(BIN_DIR) -p

clean:
	rm -r bin