BIN := taxi_manage
BIN_DIR := bin
SRC_DIR := src
PROC_DIR := proc

COMAND_FUNC_DIR := comand_function
DRIVER_FUNC_DIR := driver_function
LIST_FUNC_DIR := list_function
MENU_SCREN_DIR := menu_scren
CONVERT_DIR := convert

OBJ := bin/main.o

COMAND_FUNC_OBJ := bin/comand_function/create_driver.o bin/comand_function/del_driver.o \
bin/comand_function/get_drivers.o bin/comand_function/get_status.o bin/comand_function/send_task.o

DRIVER_FUNC_OBJ := bin/driver_function/init_driver.o bin/driver_function/send_mess_to_driver.o bin/driver_function/init_qmess.o\
bin/driver_function/init_mman.o bin/driver_function/close_mman.o

LIST_FUNC_OBJ := bin/list_function/add.o bin/list_function/get_all.o bin/list_function/get.o

MENU_SCREN_OBJ := bin/menu_scren/menu.o

CONVERT_OBJ := bin/convert/convert_char_to_int.o bin/convert/convert_int_to_char.o

.PHONY: all MAKE_DIRS clean

all: MAKE_DIRS $(BIN)

$(BIN): $(OBJ) $(COMAND_FUNC_OBJ) $(DRIVER_FUNC_OBJ) $(LIST_FUNC_OBJ) $(MENU_SCREN_OBJ) $(CONVERT_OBJ)
	gcc $(OBJ) $(COMAND_FUNC_OBJ) $(DRIVER_FUNC_OBJ) $(LIST_FUNC_OBJ) $(MENU_SCREN_OBJ) $(CONVERT_OBJ) -o $(PROC_DIR)/$@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/$(COMAND_FUNC_DIR)/%.o: $(SRC_DIR)/$(COMAND_FUNC_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/$(DRIVER_FUNC_DIR)/%.o: $(SRC_DIR)/$(DRIVER_FUNC_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/$(LIST_FUNC_DIR)/%.o: $(SRC_DIR)/$(LIST_FUNC_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/$(MENU_SCREN_DIR)/%.o: $(SRC_DIR)/$(MENU_SCREN_DIR)/%.c 
	gcc $^ -c -o $@

$(BIN_DIR)/$(CONVERT_DIR)/%.o: $(SRC_DIR)/$(CONVERT_DIR)/%.c 
	gcc $^ -c -o $@

MAKE_DIRS:
	mkdir $(BIN_DIR) -p
	mkdir $(BIN_DIR)/$(COMAND_FUNC_DIR) -p
	mkdir $(BIN_DIR)/$(DRIVER_FUNC_DIR) -p
	mkdir $(BIN_DIR)/$(LIST_FUNC_DIR) -p
	mkdir $(BIN_DIR)/$(MENU_SCREN_DIR) -p
	mkdir $(BIN_DIR)/$(CONVERT_DIR) -p
	mkdir $(PROC_DIR) -p

clean:
	rm $(BIN_DIR) -r
	rm $(PROC_DIR) -r
	