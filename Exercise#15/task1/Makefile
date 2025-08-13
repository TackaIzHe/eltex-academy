BIN1 := kill_proc 
BIN2 := main
OBJ1 := bin/kill_proc.o 
OBJ2 := bin/main.o
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN1) $(BIN2)

$(BIN1): $(OBJ1) 
	gcc $(OBJ1) -o $(PROC_DIR)/$@

$(BIN2): $(OBJ2) 
	gcc $(OBJ2) -o $(PROC_DIR)/$@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

MAKE_DIRS:
	mkdir $(BIN_DIR) -p
	mkdir $(PROC_DIR) -p

clean:
	rm -r bin
	rm -r proc