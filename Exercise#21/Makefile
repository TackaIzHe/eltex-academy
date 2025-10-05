SERVER_BIN := server
CLIENT_BIN := client
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc

SERVER_DIR := server
SERVER_OBJ := server.o convert_int_to_char.o new_con.o sig_func.o

CLIENT_DIR := client
CLIENT_OBJ := client.o

TOGETHER_OBJ := ../check_sum.o ../get_mess.o ../open_socket.o ../send_mess.o ../set_header.o


.PHONY: all MAKE_DIRS clean together_obj

all: MAKE_DIRS together_obj $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_OBJ)
	cd bin/server && gcc $(SERVER_OBJ) $(TOGETHER_OBJ) -o ../../$(PROC_DIR)/$@ && cd ../..

%.o: src/server/%.c
	gcc $^ -c -o $(BIN_DIR)/$(SERVER_DIR)/$@
	
$(CLIENT_BIN): $(CLIENT_OBJ) 
	cd bin/client && gcc $(CLIENT_OBJ) $(TOGETHER_OBJ) -o ../../$(PROC_DIR)/$@ && cd ../..

%.o: src/client/%.c 
	gcc $^ -c -o $(BIN_DIR)/$(CLIENT_DIR)/$@

together_obj: 
	$(MAKE) -C src

MAKE_DIRS:
	mkdir $(BIN_DIR) -p
	mkdir $(PROC_DIR) -p
	mkdir $(BIN_DIR)/$(SERVER_DIR) -p
	mkdir $(BIN_DIR)/$(CLIENT_DIR) -p

clean:
	rm $(BIN_DIR) -r
	rm $(PROC_DIR) -r
	