BIN := main
OBJ := bin/main.o bin/getFileAndDir.o bin/UI/mcInit.o bin/UI/UIInit.o bin/UI/moveCurs.o bin/UI/fillLine.o bin/UI/fillFileAndFolder.o
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc
UI_DIR := src/UI
UI_BIN_DIR := bin/UI

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN)

$(BIN): $(OBJ)
	gcc $(OBJ) -o $(PROC_DIR)/$@ -lncurses

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

$(UI_BIN_DIR)/%.o: $(UI_DIR)/%.c 
	gcc $^ -c -o $@


MAKE_DIRS:
	mkdir $(UI_BIN_DIR) -p
	mkdir $(BIN_DIR) -p
	mkdir $(PROC_DIR) -p

clean:
	rm -r bin proc