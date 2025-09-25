BIN := taxi_manage
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc

COMAND_FUNC_DIR := comand_function
DRIVER_FUNC_DIR := driver_function
LIST_FUNC_DIR := list_function

OBJ := bin/main.o

COMAND_FUNC_OBJ := bin/comand_function/create_driver.o bin/comand_function/del_driver.o \
bin/comand_function/get_drivers.o bin/comand_function/get_status.o bin/comand_function/send_task.o

DRIVER_FUNC_OBJ := bin/driver_function/init_driver.o bin/driver_function/sig_to_driver.o

LIST_FUNC_OBJ := bin/list_function/add.o bin/list_function/del.o bin/list_function/get_all.o bin/list_function/get.o bin/list_function/free_list.o

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN)

$(BIN): $(OBJ) $(COMAND_FUNC_OBJ) $(DRIVER_FUNC_OBJ) $(LIST_FUNC_OBJ)
	gcc $(OBJ) $(COMAND_FUNC_OBJ) $(DRIVER_FUNC_OBJ) $(LIST_FUNC_OBJ) -o $(PROC_DIR)/$@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/$(COMAND_FUNC_DIR)/%.o: $(SRC_DIR)/$(COMAND_FUNC_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/$(DRIVER_FUNC_DIR)/%.o: $(SRC_DIR)/$(DRIVER_FUNC_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/$(LIST_FUNC_DIR)/%.o: $(SRC_DIR)/$(LIST_FUNC_DIR)/%.c 
	gcc $^ -c -o $@

MAKE_DIRS:
	mkdir $(BIN_DIR) -p
	mkdir $(BIN_DIR)/$(COMAND_FUNC_DIR) -p
	mkdir $(BIN_DIR)/$(DRIVER_FUNC_DIR) -p
	mkdir $(BIN_DIR)/$(LIST_FUNC_DIR) -p
	mkdir $(PROC_DIR) -p

clean:
	rm $(BIN_DIR) -r
	rm $(PROC_DIR) -r
	