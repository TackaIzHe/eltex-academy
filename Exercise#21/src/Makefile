BIN_DIR := bin
SRC_DIR := src

TOGETHER_OBJ := check_sum.o get_mess.o open_socket.o send_mess.o set_header.o

.PHONY: all

all: $(TOGETHER_OBJ)

%.o: %.c 
	gcc $^ -c -o ../$(BIN_DIR)/$@
