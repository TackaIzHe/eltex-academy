SERVER_BIN := server
CLIENT_BIN := client
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc

SERVER_DIR := server

SERVER_OBJ := main.o

TOGETHER_OBJ := check_sum.o


.PHONY: all MAKE_DIRS clean together_obj

all: MAKE_DIRS together_obj $(SERVER_BIN)

$(SERVER_BIN): $(SERVER_OBJ) 
	gcc $(BIN_DIR)/$(SERVER_DIR)/$(SERVER_OBJ) $(BIN_DIR)/$(TOGETHER_OBJ) -o $(PROC_DIR)/$@


%.o: $(SRC_DIR)/$(SERVER_DIR)/%.c 
	gcc $^ -c -o $(BIN_DIR)/$(SERVER_DIR)/$@

together_obj: 
	$(MAKE) -C src

MAKE_DIRS:
	mkdir $(BIN_DIR) -p
	mkdir $(PROC_DIR) -p
	mkdir $(BIN_DIR)/$(SERVER_DIR) -p

clean:
	rm $(BIN_DIR) -r
	rm $(PROC_DIR) -r
	