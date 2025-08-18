BIN1 := server 
BIN2 := tcp_client
BIN3 := udp_client
OBJ1 := bin/server.o bin/wait_con.o bin/tcp_new_con.o bin/udp_new_con.o
OBJ2 := bin/tcp_client.o
OBJ3 := bin/udp_client.o
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN1) $(BIN2) $(BIN3)

$(BIN1): $(OBJ1) 
	gcc $(OBJ1) -o $(PROC_DIR)/$@

$(BIN2): $(OBJ2) 
	gcc $(OBJ2) -o $(PROC_DIR)/$@

$(BIN3): $(OBJ3) 
	gcc $(OBJ3) -o $(PROC_DIR)/$@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

MAKE_DIRS:
	mkdir $(BIN_DIR) -p
	mkdir $(PROC_DIR) -p

clean:
	rm -r bin
	rm -r proc