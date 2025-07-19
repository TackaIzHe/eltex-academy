BIN := main
OBJ1 := bin/main.o bin/getFileAndDir.o bin/UI/mcInit.o bin/UI/UIInit.o bin/UI/moveCurs.o bin/UI/fillLine.o bin/UI/fillFileAndFolder.o bin/UI/changeDir.o bin/getPath.o
OBJ2:= bin/FileListFunc/clearList.o bin/FileListFunc/getLenght.o bin/FileListFunc/push.o bin/FileListFunc/getItem.o
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc
UI_DIR := src/UI
UI_BIN_DIR := bin/UI
FILE_LIST_DIR := src/FileListFunc
FILE_LIST_BIN_DIR := bin/FileListFunc

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN)

$(BIN): $(OBJ1) ${OBJ2}
	gcc $(OBJ1) $(OBJ2) -o $(PROC_DIR)/$@ -lncurses

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

$(FILE_LIST_BIN_DIR)/%.o: $(FILE_LIST_DIR)/%.c 
	gcc $^ -c -o $@

$(UI_BIN_DIR)/%.o: $(UI_DIR)/%.c 
	gcc $^ -c -o $@


MAKE_DIRS:
	mkdir $(BIN_DIR) -p
	mkdir $(UI_BIN_DIR) -p
	mkdir $(PROC_DIR) -p
	mkdir $(FILE_LIST_BIN_DIR) -p

clean:
	rm -r bin proc