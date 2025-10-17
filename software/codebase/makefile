CC = gcc
FLAGS = -Wall -Iinclude -g -pthread
PIFLAG = -lpigpio -lrt
LIBFLAG = -Lbin -lmotor

BIN_DIR = bin
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))
LIB = $(BIN_DIR)/libmotor.a
EXEC = ./final

all : $(EXEC);

$(EXEC): $(LIB) $(OBJ) | $(BIN_DIR)
	$(CC) $(FLAGS) -o $@ main.cpp $(LIBFLAG)

LIB : $(OBJ) 
	ar rcs $(LIB) $^

BIN_DIR/%.o : $(SRC) | $(BIN_DIR)
	$(CC) $(FLAGS) -c -o -OBJ $@  $< $(PIFLAG)

BIN_DIR :
	mkdir -p (BIN_DIR);

