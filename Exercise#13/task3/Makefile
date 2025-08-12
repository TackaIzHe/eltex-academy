BIN1 := server 
BIN2 := client
OBJ1 := bin/server.o bin/new_con.o
OBJ2 := bin/client/client.o bin/client/connect_func.o bin/client/get_mess_func.o bin/client/send_func.o bin/client/get_users.o
OBJ_UI := bin/client/UI/s_init.o bin/client/UI/print_win.o bin/client/UI/input_func.o 
BIN_DIR := bin
SRC_DIR := src
CLIENT_DIR := bin/client
PROC_DIR := proc
UI_DIR := bin/client/UI
SRC_UI_DIR := src/UI

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN1) $(BIN2)

$(BIN1): $(OBJ1) 
	gcc $(OBJ1) -o $(PROC_DIR)/$@

$(BIN2): $(OBJ_UI) $(OBJ2)  
	gcc $(OBJ2) $(OBJ_UI) -o $(PROC_DIR)/$@ -lncurses

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

$(UI_DIR)/%.o: $(SRC_UI_DIR)/%.c
	gcc $^ -c -o $@

MAKE_DIRS:
	mkdir $(BIN_DIR) -p
	mkdir $(CLIENT_DIR) -p
	mkdir $(UI_DIR) -p
	mkdir $(PROC_DIR) -p

clean:
	rm -r bin