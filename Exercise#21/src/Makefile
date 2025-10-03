BIN_DIR := bin
SRC_DIR := src

TOGETHER_OBJ := check_sum.o


.PHONY: all

all: $(TOGETHER_OBJ)

%.o: %.c 
	gcc $^ -c -o ../$(BIN_DIR)/$@
